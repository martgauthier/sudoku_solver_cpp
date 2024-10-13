#include "utils.h"
#include <iostream>

#ifdef _W32
#include <windows.h>
#endif

void resetCursorPosition() {
    #ifdef _W32
        COORD coord = {0, 0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    #else//should work the same for linux and macOS
        std::cout << "\033[H";
    #endif
}

void clearTerminal() {
    #ifdef _W32
        COORD topLeft  = { 0, 0 };
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(console, &screen);
        FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        SetConsoleCursorPosition(console, topLeft);
    #else
        std::cout << "\033[2J";
    #endif
}

#ifdef _WIN32 

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

//source : https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
void activateVirtualTerminal()
{       
    HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode( handleOut , &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;            
    SetConsoleMode( handleOut , consoleMode );
}
#endif