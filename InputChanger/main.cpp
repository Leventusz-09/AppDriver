#include <iostream>
#include <windef.h>
#include <winuser.h>
#include <windows.h>

#define dMin 5

using namespace std;

void keyUp(WORD keyCode){
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = keyCode;
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
}
void keyDown(WORD keyCode, bool raise = false, int raiseAfter = 100){
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = keyCode;
    input.ki.dwFlags = KEYEVENTF_SCANCODE;

    SendInput(1, &input, sizeof(INPUT));

    if(raise){
        Sleep(raiseAfter);
        keyUp(keyCode);
    }
}

int main_test(){
    Sleep(3000);
    int i=1;
    while (++i)
    {
        keyDown(VK_UP, 1, 100);
        //Sleep(100);
    }
    return 0;
}

int main(){
    cout << "Starting...";

    POINT mouse;
    mouse.x = 0;
    mouse.y = 0;
    
    POINT last;
    last.x = 0;
    last.y = 0;

    
    while(1){
        last.x = mouse.x;
        last.y = mouse.y;

        GetCursorPos(&mouse);

        WORD command = VK_ACCEPT;


        if(mouse.x - last.x < -dMin){
            command = VK_LEFT;
        }
        if(mouse.x - last.x > dMin){
            command = VK_RIGHT;
        }
        if(mouse.y - last.y > dMin){
            command = VK_DOWN;
        }
        if(mouse.y - last.y < -dMin){
            command = VK_UP;
        }

        if(command == VK_ACCEPT){
            Sleep(100);
            continue;
        }

        keyDown(command);
        Sleep(100);
        keyUp(command);

        //cout << comméééllkááéééáléand << endl;

        //cout << "x=" << mouse.x << "\ny=" << mouse.y << endl;

        //Sleep(100);
    }
        

    return 0;
}