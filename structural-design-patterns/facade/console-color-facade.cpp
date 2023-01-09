#include <string>
#include <iostream>
#include <windows.h>

enum class Color { Red, Green, Blue, White };

class Console
{
    inline static HANDLE m_std;
    static Console m_instance;

    static DWORD getColor(const Color color)
    {
        switch (color) {
            case Color::Red:
                return FOREGROUND_RED;
            case Color::Green:
                return FOREGROUND_GREEN;
            case Color::Blue:
                return FOREGROUND_BLUE;
            case Color::White:
            default:
                return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        }
    }
    Console() { m_std = GetStdHandle(STD_OUTPUT_HANDLE); };

public:
    static void write(const std::string &text, const Color color = Color::White)
    {
        CONSOLE_SCREEN_BUFFER_INFO csinfo{};
        if (!GetConsoleScreenBufferInfo(m_std, &csinfo)) {
            throw std::runtime_error("Error getting console info");
        }
        SetConsoleTextAttribute(m_std, getColor(color));
        DWORD written{};
        WriteConsoleA(m_std, text.c_str(), text.size(), &written, nullptr);
        SetConsoleTextAttribute(m_std, csinfo.wAttributes);
    }
    static void writeln(const std::string &text, const Color color = Color::White) { write(text + '\n', color); }
};

Console Console::m_instance;

int main()
{
    Console::writeln("Hello World", Color::Red);
    std::cout << "Default color must be\n";
    printf("Still default color\n");
    Console::writeln("Diferent Color", Color::Blue);
}
