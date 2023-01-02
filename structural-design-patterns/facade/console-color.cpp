#include <windows.h>
#include <string>
#include <iostream>

int main(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csinfo{};
    if(!GetConsoleScreenBufferInfo(hConsole, &csinfo)){
        std::cout << "Error getting console info\n";
        return 1;
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    std::string text{"Hello World"};
    DWORD written{};
    WriteConsoleA(hConsole, text.c_str(), text.size(), &written, nullptr);
    std::cout << "Using cout\n";
    printf("Using printf\n");
    SetConsoleTextAttribute(hConsole, csinfo.wAttributes);
}
