#include <iostream>
#include <Windows.h>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <conio.h>

#include "input.h"
#include "functions.h"

int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    std::cout << "QCLICKER v1.1 (20042025)\n\n[ 1 ] MOVE-CLICK simulation\n[ 2 ] ONLY-CLICK simulation\n[ 3 ] MOVE-CLICK CYCLIC simulation\n[ 4 ] ONLY-CLICK CYCLIC simulation\n[ 5 ] Auto-clicker\n[ 6 ] Get cursor position ";
    
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

    if (GetAsyncKeyState(0x33) || GetAsyncKeyState(VK_NUMPAD3))
    {
        simulation(false, 10, true);
    }

    else if (GetAsyncKeyState(0x34) || GetAsyncKeyState(VK_NUMPAD4))
    {
        int d;
        std::cout << "\n\nEnter the delay between clicks (ms) (default: 10): ";
        keyPress(0x31); // 1
        keyPress(0x30); // 0    // 10 ms
        std::cin >> d;
        simulation(true, d, true);
    }

    else if (GetAsyncKeyState(0x35) || GetAsyncKeyState(VK_NUMPAD5))
    {
        int d = 10;
        std::cout << "\n\nEnter the delay between clicks (ms): ";
        std::cin >> d;

        autoClicker(d);
    }

    else if (GetAsyncKeyState(0x36) || GetAsyncKeyState(VK_NUMPAD6))
    {
        getCursorPosition();
    }

    int e;
    std::cout << "\nDONE";
    std::cin >> e;
}
