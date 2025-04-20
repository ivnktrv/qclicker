#include <Windows.h>

void leftMouseClick()
{
    INPUT input[2] = { 0 };

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(2, input, sizeof(INPUT));
}

void rightMouseClick()
{
    INPUT input[2] = { 0 };

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    SendInput(2, input, sizeof(INPUT));
}

/*
void mouseWheel(int delta)
{
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    input.mi.mouseData = delta;
    SendInput(1, &input, sizeof(INPUT));
}

void leftMouseHoldDown()
{
    INPUT input[1] = { 0 };

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    SendInput(1, input, sizeof(INPUT));
}

void leftMouseHoldUp()
{
    INPUT input[1] = { 0 };

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(1, input, sizeof(INPUT));
}

void rightMouseHoldDown()
{
    INPUT input[1] = { 0 };

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    SendInput(1, input, sizeof(INPUT));
}

void rightMouseHoldUp()
{
    INPUT input[1] = { 0 };

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    SendInput(1, input, sizeof(INPUT));
}
*/
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