#include <iostream>
#include <Windows.h>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <conio.h>

#include "input.h"


struct InputData
{
    int posX;
    int posY;
    int clickType;
    //int mouseWheel;
    int keyCode;
};

std::vector<InputData> pos;

std::vector<InputData> setPos(bool onlyClick = false) {

    /*
    (posX, posY, clickType, mouseWheel, keyCode)

    posX, posY - cursor position
    clickType: 0 - none, 1 - left, 2 - right
    keyCode - key press (0 - not presset)
    */
    

    int last_click_x = -1;
    int last_click_y = -1;

    int last_rclick_x = -1;
    int last_rclick_y = -1;

    DWORD currentTime = GetTickCount();
    bool keyStates[256] = { false };
    DWORD lastPressTime[256] = { 0 };
    
    while (true)
    {
        POINT p;
        
        int lastKeyCode = -1;
        GetCursorPos(&p);


        for (int i = 0x08; i <= 0xFE; i++) 
        {
            bool currentState = (GetAsyncKeyState(i) & 0x8000) != 0;

            if (currentState) {
                // Первое нажатие
                if (!keyStates[i]) {
                    pos.push_back({ p.x, p.y, 0, i });
                    lastPressTime[i] = currentTime;
                }
                // Автоповтор после 500 мс
                else if (currentTime - lastPressTime[i] > 10) {
                    pos.push_back({ p.x, p.y, 0, i });
                    lastPressTime[i] = currentTime;
                }
            }

            keyStates[i] = currentState;
        }
        /*for (int i = 0x41; i <= 0x5A; i++) {

            if (GetAsyncKeyState(i)) {
                Sleep(10);
                pos.push_back({ p.x, p.y, 0, 0, i });
            }
        }*/
        
        if (!onlyClick)
        {
            Sleep(10);
            pos.push_back({ p.x, p.y, 0, 0 });
            
        }
        
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            Sleep(500);
            break;
        }
        if (GetAsyncKeyState(VK_LBUTTON))
        {
                // Check if it's a duplicate click
            if (p.x != last_click_x || p.y != last_click_y)
            {
                Sleep(10);
                pos.push_back({ p.x, p.y, 1, 0 });
                last_click_x = p.x;
                last_click_y = p.y;
            }
            
        }
        else {
            last_click_x = -1;
            last_click_y = -1;
        }
        if (GetAsyncKeyState(VK_RBUTTON))
        {
            // Check if it's a duplicate click
            if (p.x != last_rclick_x || p.y != last_rclick_y)
            {
                Sleep(10);
                pos.push_back({ p.x, p.y, 2, 0 });
                last_rclick_x = p.x;
                last_rclick_y = p.y;
            }

        }
        else {
            last_rclick_x = -1;
            last_rclick_y = -1;
        }

    }

    std::cout << "ABORT\n\n- - - - - - - -\n";
    
    return pos;
}

int simulation(bool onlyClick = false, int delay = 10, bool cyclic = false)
{
    std::cout << "\n\n[ MOVE MOUSE ] - MOVE CURSOR\n[ LEFT BUTTON ] - LEFT CLICK\n\nPRESS [ ESC ] TO ABORT\n\n";
    Sleep(100);


    if (onlyClick)
    {
        pos = setPos(onlyClick = true);
    }
    else
    {
        pos = setPos();
    }

    bool isLeftPressed = false;
    bool wasLeftPressed = false;

    if (cyclic == true) 
    {
        while (true)
        {
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                std::cout << "ABORT";
                break;
            }
            for (const auto& el : pos)
            {
                Sleep(delay);

                SetCursorPos(el.posX, el.posY);
                std::cout << "[ MOVE ] " << "" << el.posX << " : " << el.posY << std::endl;

                if (GetAsyncKeyState(VK_ESCAPE))
                {
                    std::cout << "ABORT";
                    break;
                }
                if (el.clickType == 0)
                {

                }
                else if (el.clickType == 1)
                {
                    leftMouseClick();
                    std::cout << "[ LEFT CLICK ] " << el.posX << " : " << el.posY << std::endl;
                }
                else if (el.clickType == 2)
                {
                    rightMouseClick();
                    std::cout << "[ RIGHT CLICK ] " << "" << el.posX << " : " << el.posY << std::endl;
                }
                if (el.keyCode != 0) {
                    keyPress(el.keyCode);
                    std::cout << "[ KEY PRESSED ] " << (char)el.keyCode << std::endl;
                }
            }
        }
    }

    else
    {
        for (const auto& el : pos)
        {
            Sleep(delay);

            SetCursorPos(el.posX, el.posY);
            std::cout << "[ MOVE ] " << "" << el.posX << " : " << el.posY << std::endl;

            if (GetAsyncKeyState(VK_ESCAPE))
            {
                std::cout << "ABORT";
                break;
            }
            if (el.clickType == 0)
            {

            }
            if (el.clickType == 1)
            {
                leftMouseClick();
                std::cout << "[ LEFT CLICK ] " << el.posX << " : " << el.posY << std::endl;
            }
            if (el.clickType == 2)
            {
                rightMouseClick();
                std::cout << "[ RIGHT CLICK ] " << "" << el.posX << " : " << el.posY << std::endl;
            }
            if (el.keyCode != 0) {
                keyPress(el.keyCode);
                std::cout << "[ KEY PRESSED ] " << (char)el.keyCode << std::endl;
            }
        }
    }
    
    return 0;
}

int autoClicker(int delay)
{
    std::cout << "\n\nSET THE CURSOR AND PRESS [ S ] TO START";
    _getch();
    if (GetAsyncKeyState(0x53))
    {
        std::cout << "\nSTART\n\nPRESS [ ESC ] TO ABORT";
        POINT p;
        GetCursorPos(&p);

        while (true)
        {
            if (GetAsyncKeyState(VK_ESCAPE)) { break; }
            SetCursorPos(p.x, p.y);
            leftMouseClick();
            Sleep(delay);
        }
    }
    return 0;
}

int getCursorPosition()
{
    //std::cout << " ";
    while (true)
    {
        POINT p;
        if (GetCursorPos(&p))
        {
            std::cout << "X: " << p.x << " Y: " << p.y;
        }
        Sleep(10);

        //std::cout << "\x1B[2J\x1B[H";
        system("cls");
    }
    return 0;
}
