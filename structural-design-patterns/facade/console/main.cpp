#include "console_colors.h"

int main()
{
    Console::writeln("Hello World", Color::Red);
    std::cout << "Default color must be\n";
    printf("Still default color\n");
    Console::writeln("Diferent Color", Color::Blue);
}
