/*
 * Project: cpp-snake-vscode-win-sample
 * lisr-pcx
 * 2024-09-21
 * Include windows API for cursor movement and user input
 */

#include <iostream>
#include "snake.h"

int main()
{    
    int RetVal = 0;
    Snake SnakeGame;

    while (RetVal == 0)
    {
        RetVal = SnakeGame.Run();
    }

    Sleep(2);
    return 0;
}
