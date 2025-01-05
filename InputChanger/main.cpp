#include <iostream>
#include <windef.h>
#include <winuser.h>
#include <windows.h>
#include <fstream>
#include <vector>

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

int main(){
    cout << "Starting...";

    POINT mouse;
    mouse.x = 0;
    mouse.y = 0;
    
    POINT last;
    last.x = 0;
    last.y = 0;

    ifstream configFile("config.csv");
    vector<int> config;
    string temp;
    while (getline(configFile, temp))
        config.push_back(stoi(temp));
    configFile.close();
    
    #define minimalDelta  config[0]
    #define LEFTK         config[1]
    #define RIGHTK        config[2]
    #define UPK           config[3]
    #define DOWNK         config[4]
    #define timeUnit      config[5]
    #define resetInterval config[6]

    const int width  = ::GetSystemMetrics(SM_CXSCREEN);
    const int height = ::GetSystemMetrics(SM_CYSCREEN);

    int c = 0;

    while(1){
        last.x = mouse.x;
        last.y = mouse.y;

        GetCursorPos(&mouse);

        //WORD command = VK_ACCEPT;

        int dx = mouse.x - last.x;
        int dy = mouse.y - last.y;

        bool mx = abs(dx) > minimalDelta;
        bool my = abs(dy) > minimalDelta;

        if(mx && my){
            int sum = abs(dx) + abs(dy);

            if(dx < 0)
                keyDown(LEFTK, 1, double(timeUnit) / double(sum) * abs(dx)); //balra
            else
                keyDown(RIGHTK, 1, double(timeUnit) / double(sum) * abs(dx)); //jobbra
            
            if(dy < 0)
                keyDown(UPK, 1, double(timeUnit) / double(sum) * abs(dy)); //fel
            else
                keyDown(DOWNK, 1, double(timeUnit) / double(sum) * abs(dy)); //le   
        }else if(mx){
            if(dx < 0)
                keyDown(LEFTK, 1, timeUnit); //balra
            else
                keyDown(RIGHTK, 1, timeUnit); //jobbra
        }else if(my){
            if(dy < 0)
                keyDown(UPK, 1, timeUnit); //fel
            else
                keyDown(DOWNK, 1, timeUnit); //le   
        }else{
            Sleep(timeUnit);
        }

        if(c * timeUnit > resetInterval){
            c = 0;
            SetCursorPos(width/2, height/2);
        }else
        
        c++;
    }
        

    return 0;
}