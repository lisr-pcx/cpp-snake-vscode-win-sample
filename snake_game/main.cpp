/*
 * Project: cpp-snake-vscode-win-sample
 * lisr-pcx
 * 2024-09-21
 * Please note: it uses Windows API for cursor movement and user input
 */

#include <iostream>
#include "snake.h"

#define BOARDSIZE 12

int main()
{    
    int RetVal = 0;
    Snake SnakeGame(BOARDSIZE);

    while (RetVal == 0)
    {
        RetVal = SnakeGame.Run();
    }

    Sleep(2);
    return 0;
}
