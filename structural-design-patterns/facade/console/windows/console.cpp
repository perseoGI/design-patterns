#include <console.h>

Console Console::m_instance;

static DWORD Console::getColor(const Color color)
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

Console::Console()
{
    m_std = GetStdHandle(STD_OUTPUT_HANDLE);
};

static void Console::write(const std::string &text, const Color color = Color::White)
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
static void Console::writeln(const std::string &text, const Color color = Color::White)
{
    write(text + '\n', color);
}
