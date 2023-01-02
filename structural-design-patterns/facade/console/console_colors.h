#ifndef CONSOLE_COLORS
#define CONSOLE_COLORS

#ifdef _WIN32
#include "windows/console.h"
#elif __linux__
#include "linux/console.h"
#endif

#endif
