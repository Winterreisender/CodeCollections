#include <iostream>
#include <stdio.h>
#include <synchapi.h>
#include <windows.h>
using namespace std;

#define IS_KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? true:false) 

int main()
{
    double times;
    cout << "双发扳机已开启,长按ESC键退出" << endl;
    times = 10.0;

    while (true)
    {
        if (IS_KEY_DOWN(MOUSE_MOVED))//GetAsyncKeyState(VK_XXX))
        {
            POINT p = {};
            GetCursorPos(&p);
            // cout << "MOUSE_MOVED " << p.x << ","  << p.y << endl;
            Sleep(times);
            mouse_event(MOUSEEVENTF_LEFTDOWN, p.x, p.y, 0, 0);
            Sleep(1);
            mouse_event(MOUSEEVENTF_LEFTUP, p.x, p.y, 0, 0);

            if (GetAsyncKeyState(VK_ESCAPE))
                break;
        }
    }
    return 0;
}