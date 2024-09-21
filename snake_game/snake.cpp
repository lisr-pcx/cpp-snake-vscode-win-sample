/*
 * Project: cpp-snake-vscode-win-sample
 * lisr-pcx
 * 2024-09-21
 * Include windows API for cursor movement and user input
 */

#include "snake.h"

Snake::Snake()
{
	this->TheSnake[0].x = this->kBoardMaxWidth / 2;
	this->TheSnake[0].y = this->kBoardMaxHeight / 2;
	this->TheMouse.x = (this->kBoardMaxWidth / 2) + 3;
	this->TheMouse.y = (this->kBoardMaxHeight / 2) + 3;
	this->Direction = this->kRight;
	this->ForceDrawGrid = true;

	std::srand(5);
}

Snake::~Snake()
{
	// do nothing
}

int Snake::Run()
{
	TypePoint PrevHead = TheSnake[IdxHead];

	IdxHead++;
	// wrap around the Snake array
	if (IdxHead >= kMaxSnake)
	{
		IdxHead = 0;
	}

	// Get user input (it works only for Win OS)
	if (GetAsyncKeyState(VK_ESCAPE) != 0)
    {
		// press ESC to force exit game
        return (-1);
    }
	if (GetAsyncKeyState(VK_UP) != 0)
    {
		if (Direction != kDown)
		{
			Direction = kUp;
		}        
    }
	if (GetAsyncKeyState(VK_RIGHT) != 0)
    {
		if (Direction != kLeft)
		{
			Direction = kRight;
		}        
    }
	if (GetAsyncKeyState(VK_DOWN) != 0)
    {
		if (Direction != kUp)
		{
			Direction = kDown;
		}        
    }
	if (GetAsyncKeyState(VK_LEFT) != 0)
    {
		if (Direction != kRight)
		{
			Direction = kLeft;
		}        
    }
	
	// move
	switch (Direction)
	{
		case kUp:
			TheSnake[IdxHead].x = PrevHead.x;
			TheSnake[IdxHead].y = this->MakePointYCircular(PrevHead.y - 1);
			break;
		case kRight:
			TheSnake[IdxHead].x = this->MakePointXCircular(PrevHead.x + 1);
			TheSnake[IdxHead].y = PrevHead.y;
			break;
		case kDown:
			TheSnake[IdxHead].x = PrevHead.x;
			TheSnake[IdxHead].y = this->MakePointYCircular(PrevHead.y + 1);
			break;
		case kLeft:
			TheSnake[IdxHead].x = this->MakePointXCircular(PrevHead.x - 1);
			TheSnake[IdxHead].y = PrevHead.y;
			break;
		default:
			// ERR: not valid direction
			break;
	};

	// draw this new head on screen
	AddPointOnScreen = TheSnake[IdxHead];

	// eat the mouse (if over head)
	if ( (TheSnake[IdxHead].x == TheMouse.x) && 
		 (TheSnake[IdxHead].y == TheMouse.y) )
	{
		// place a new mouse
		TheMouse = NewMousePosition();
	}
	else
	{
		// clear the (old) tail on screen
		ClearPointOnScreen = TheSnake[IdxTail];

		// no mouse
		IdxTail++;
		// wrap around the Snake array
		if (IdxTail >= kMaxSnake)
		{
			IdxTail = 0;
		}
	}

	// check collision
	for (unsigned int i=IdxTail; i < IdxHead; i++)
	{
		if ((TheSnake[IdxHead].x == TheSnake[i].x) &&
			(TheSnake[IdxHead].y == TheSnake[i].y))
		{
			// game over
			std::cout << "  >>> Game Over! <<<\n";
			return -1;
		}
	}

	// check win
	if (IdxHead == (IdxTail - 1))
	{
		std::cout << "  ^^^ YOU WIN :) ^^^\n";
		return 1;
	}

	// Update user screen
	this->Draw();

	// Kind of fame frame rate
	Sleep(500);

	return 0;
}

void Snake::Draw()
{
	// Draw and empty char (for snake tail)
	COORD Pos = {(short) ClearPointOnScreen.x, (short) ClearPointOnScreen.y};
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
    std::cout << " ";

	// Draw new body (for snake head)
    Pos = {(short) AddPointOnScreen.x, (short) AddPointOnScreen.y};
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
    std::cout << "*";

	// Draw the (new) mouse
    Pos = {(short) TheMouse.x, (short) TheMouse.y};
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
    std::cout << "M";

	// Draw board "limit angle"
    Pos = {(short) kBoardMaxHeight, (short) kBoardMaxWidth};
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
    std::cout << "+";

	if (this->ForceDrawGrid == true)
	{
		this->DrawGrid();
		// Do it once
		this->ForceDrawGrid = false;
	}
}

/* Private */

unsigned int Snake::MakePointXCircular(int val)
{
	if (val < 0)
	{
		return (this->kBoardMaxWidth - 1);
	}
	else if (val >= this->kBoardMaxWidth)
	{
		return 0;
	}
	else
	{
		return ((unsigned int) val);
	}
}

unsigned int Snake::MakePointYCircular(int val)
{
	if (val < 0)
	{
		return (this->kBoardMaxHeight - 1);
	}
	else if (val >= this->kBoardMaxHeight)
	{
		return 0;
	}
	else
	{
		return ((unsigned int) val);
	}
}

Snake::TypePoint Snake::NewMousePosition()
{
	bool Valid = false;
	TypePoint Position;

	while (Valid == false)
	{
		Position.x = rand() % this->kBoardMaxWidth;
		Position.y = rand() % this->kBoardMaxHeight;
		Valid = true;

		for (unsigned int i = IdxTail; i < IdxHead; i++)
		{
			if ((Position.x == TheSnake[i].x) &&
				(Position.y == TheSnake[i].y))
			{
				Valid = false;
			}
		}
	}
	return Position;
}

void Snake::DrawGrid()
{
	COORD Pos = {0, 0};
	for (short r = 0; r <= this->kBoardMaxHeight; r++)
	{
		Pos = {(short) kBoardMaxWidth, r};
		SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		std::cout << "|";
	}
	for (short c = 0; c <= this->kBoardMaxWidth; c++)
	{
		Pos = {c, (short) kBoardMaxHeight};
		SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		std::cout << "-";
	}
}
