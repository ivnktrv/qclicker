#include <iostream>
#include <Windows.h>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <conio.h>

void leftClick()
{
    INPUT input[2] = { 0 };

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(2, input, sizeof(INPUT));
}

void keyPress(int keyCode) 
{
    INPUT input[2] = { 0 };

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = keyCode;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = keyCode;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, input, sizeof(INPUT));
}

std::vector<std::tuple<int, int, int>> setPos(bool onlyClick = false) {
    
    std::vector<std::tuple<int, int, int>> pos;
    
    int last_click_x = -1;
    int last_click_y = -1;

    while (true) 
    {
        POINT p;
        if (!onlyClick) 
        {
            if (GetCursorPos(&p)) 
            {
                Sleep(10);
                pos.push_back({ p.x, p.y, 0 });
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE)) 
        {
            Sleep(100);
            break;
        }
        if (GetAsyncKeyState(VK_LBUTTON))
        {
            if (GetCursorPos(&p)) 
            {
                // Check if it's a duplicate click
                if (p.x != last_click_x || p.y != last_click_y) 
                {
                    Sleep(10);
                    pos.push_back({ p.x, p.y, 1 });
                    last_click_x = p.x;
                    last_click_y = p.y;
                }
            }
        }
        else {
            last_click_x = -1;
            last_click_y = -1;
        }
    }

    std::cout << "ABORT\n\n- - - - - - - -\n";

    for (auto it = pos.begin(); it != pos.end(); ++it) {
        if (std::get<2>(*it) == 1) {
            bool offset_flag = true;
            for (auto it2 = std::next(it); it2 != pos.end(); ++it2) {
                if (std::get<0>(*it) == std::get<0>(*it2) &&
                    std::get<1>(*it) == std::get<1>(*it2) &&
                    std::get<2>(*it2) == 1) {
                    if (offset_flag) {
                        std::get<1>(*it2) += 1;
                    }
                    offset_flag = !offset_flag;
                }
                else {
                    offset_flag = true;
                }
            }
        }
    }
    return pos;
}

int simulation(bool onlyClick = false, int delay = 10)
{
    std::cout << "\n\n[ MOVE MOUSE ] - MOVE CURSOR\n[ LEFT BUTTON ] - LEFT CLICK\n\nPRESS [ ESC ] TO ABORT\n\n";
    Sleep(100);

    std::vector<std::tuple<int, int, int>> pos;

    if (onlyClick)
    {
        pos = setPos(onlyClick = true);
    }
    else 
    {
        pos = setPos();
    }

    for (const auto& el : pos) 
    {
        ShowCursor(TRUE);
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            std::cout << "ABORT";
            break;
        }
        if (std::get<2>(el) == 0)
        {
            SetCursorPos(std::get<0>(el), std::get<1>(el));
            std::cout << "[ MOVE ] " << "" << std::get<0>(el) << " : " << std::get<1>(el) << std::endl;
        }
        else
        {
            SetCursorPos(std::get<0>(el), std::get<1>(el));
            leftClick();
            std::cout << "[ CLICK ] " << "" << std::get<0>(el) << " : " << std::get<1>(el) << std::endl;
        }
        Sleep(delay);
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
            leftClick();
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

int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    /*
    while (true) 
    {
        POINT p;
        if (GetCursorPos(&p))
        {
            std::cout << "X: "<< p.x << " " << "Y: " <<  p.y;
        }
        Sleep(5);
        
        std::cout << "\x1B[2J\x1B[H";
    }*/
    std::cout << "QCLICKER v1.0 (19042025)\n\n[ 1 ] MOVE-CLICK simulation\n[ 2 ] ONLY-CLICK simulation\n[ 3 ] Auto-clicker\n[ 4 ] Get cursor position ";
    
    _getch();
    if (GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1))
    {
        simulation();
    }
    else if (GetAsyncKeyState(0x32) || GetAsyncKeyState(VK_NUMPAD2))
    {
        int d;
        std::cout << "\n\nEnter the delay between clicks (ms) (default: 10): ";
        keyPress(0x31); // 1
        keyPress(0x30); // 0    // 10 ms
        std::cin >> d;
        simulation(true, d);
    }
    else if (GetAsyncKeyState(0x33) || GetAsyncKeyState(VK_NUMPAD3))
    {
        int d = 10;
        std::cout << "\n\nEnter the delay between clicks (ms): ";
        std::cin >> d;

        autoClicker(d);
    }
    else if (GetAsyncKeyState(0x34) || GetAsyncKeyState(VK_NUMPAD4))
    {
        getCursorPosition();
    }

    int e;
    std::cout << "DONE";
    std::cin >> e;
}
