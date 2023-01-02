#ifndef CONSOLE
#define CONSOLE
#include <string>
#include <iostream>

enum class Color { Red, Green, Blue, White };

class Console
{
    static int getColor(const Color color);
    Console();
public:
    static void write(const std::string &text, const Color color = Color::White);
    static void writeln(const std::string &text, const Color color = Color::White);
};

#endif
