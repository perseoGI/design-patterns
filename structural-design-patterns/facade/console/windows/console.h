#ifndef CONSOLE
#define CONSOLE
#include <string>
#include <iostream>
#include <windows.h>

enum class Color { Red, Green, Blue, White };

class Console
{
    inline static HANDLE m_std;
    static Console m_instance;

    static DWORD getColor(const Color color);
    Console();
public:
    static void write(const std::string &text, const Color color = Color::White);
    static void writeln(const std::string &text, const Color color = Color::White);
};

#endif
