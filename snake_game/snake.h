/*
 * Project: cpp-snake-vscode-win-sample
 * lisr-pcx
 * 2024-09-21
 * Include windows API for cursor movement and user input
 */

#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_BOARD_SIZE		10		// game area is a square of this size

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>

class Snake
{

public:

	Snake();
	~Snake();

	/*
	 * Method: Run()
	 * Classic game loop (manage the user inputs, update the 
	 * snake/mouse position).
	 * Return:
	 *		0	: still playing
	 *		-1	: game over
	 *		1	: win
	 */

	int Run();

	/*
	 * Method: Draw()
	 * Draw all the cells on the console screen (windows lib)
	 */

	void Draw();

protected:

private:

	typedef struct
	{
		unsigned int x;
		unsigned int y;
	} TypePoint;

	typedef enum
	{
		kUp		= 0,
		kRight	= 1,
		kDown	= 2,
		kLeft	= 3
	} TypeDir;

	const unsigned int kBoardMaxWidth = SNAKE_BOARD_SIZE;
	const unsigned int kBoardMaxHeight = SNAKE_BOARD_SIZE;
	const unsigned int kMaxSnake = (SNAKE_BOARD_SIZE * SNAKE_BOARD_SIZE) - 1;

	TypePoint TheSnake[ ((SNAKE_BOARD_SIZE * SNAKE_BOARD_SIZE) - 1) ];
	TypePoint TheMouse;

	TypeDir Direction;

	TypePoint ClearPointOnScreen;
	TypePoint AddPointOnScreen;

	unsigned int IdxHead = 0;
	unsigned int IdxTail = 0;

	bool ForceDrawGrid = false;

	unsigned int MakePointXCircular(int val);
	unsigned int MakePointYCircular(int val);

	TypePoint NewMousePosition();

	void DrawGrid();
};

#endif // !SNAKE_H
