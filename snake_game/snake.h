/*
 * Project: cpp-snake-vscode-win-sample
 * lisr-pcx
 * 2024-09-21
 * Include windows API for cursor movement and user input
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include <deque>
#include <vector>

#define SNAKE_SYMBOOL	'*'
#define MOUSE_SYMBOOL	'M'
#define BLANK_SYMBOOL	' '

class Snake
{
public:

	static constexpr short kDefaultBoardSize = 10;

	/*
	 * Method: Constructor
	 * Create the square board square for the game.
	 */
	Snake(unsigned short board_size);
	~Snake();

	/*
	 * Method: Run
	 * Classic game loop (manage the user inputs, update the snake/mouse position).
	 * Return:
	 *		0	: still playing
	 *		-1	: game over
	 *		1	: win
	 */
	int Run();

	/*
	 * Method: Draw
	 * Draw all the elements inside _ItemsToDraw.
	 * This variabile is refreshed at each game cycle.
	 */
	void Draw();	

protected:

private:

	typedef struct
	{
		short x;
		short y;
	} TypePoint;

	typedef enum
	{
		kUp		= 0,
		kRight	= 1,
		kDown	= 2,
		kLeft	= 3
	} TypeDir;

	typedef struct
	{
		TypePoint 	pos;
		char		symbol;
	} TypeGraphicsElement;

	short 					_BoardMaxWidth = 0;
	short 					_BoardMaxHeight = 0;
	unsigned int 			_MaxSnake = 0;	
	std::deque<TypePoint> 	_TheSnake;
	TypeDir 				_TheSnakeDirection;
	TypePoint 				_TheMouse;
	
	std::vector<TypeGraphicsElement>	_ItemsToDraw;

	/*
	 * Method: NewMousePosition
	 * Place the mouse in a random (free) coordinate
	 */
	TypePoint NewMousePosition();

	/*
	 * Method: MakePoint..Circular
	 * Manage the "wrap around" of a single coordinate
	 * around the board corners.
	 */
	short MakePointXCircular(const short value);
	short MakePointYCircular(const short value);

	/*
	 * Method: CheckCollision
	 * Return true when the coordinates of "target"
	 * are over the snake body
	 */
	bool CheckCollision(const TypePoint target);

	/*
	 * Method: DrawGrid
	 * Draw the borders of game area
	 */
	void DrawGrid();
};

#endif // !SNAKE_H