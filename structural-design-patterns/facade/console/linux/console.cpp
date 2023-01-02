#include "console.h"
#include <iostream>

Console::Console()
{
}

int Console::getColor(const Color color)
{
    switch (color) {
        case Color::Red:
            system("tput setaf 1");
            break;
        case Color::Green:
            system("tput setaf 2");
            break;
        case Color::Blue:
            system("tput setaf 4");
            break;
        default:
            system("tput sgr0");
    }
    return 0;
}
void Console::write(const std::string &text, Color color)
{
    getColor(color);
    std::cout << text << std::flush;
    system("tput sgr0");
}
void Console::writeln(const std::string &text, Color color)
{
    write(text + '\n', color);
}
