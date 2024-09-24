/*
 * Project: cpp-snake-vscode-win-sample
 * lisr-pcx
 * 2024-09-21
 * Include windows API for cursor movement and user input
 */

#include "snake.h"

Snake::Snake(unsigned short board_size) : 
_BoardMaxWidth(kDefaultBoardSize),
_BoardMaxHeight(kDefaultBoardSize)
{
	std::srand(5);

	// WARNING: invalid size will force to default value
	if (board_size > 0)
	{
		_BoardMaxWidth = board_size;
		_BoardMaxHeight = board_size;
	}

	_MaxSnake = (_BoardMaxWidth * _BoardMaxHeight) - 1;
	TypePoint SnakeBody;
	SnakeBody.x = _BoardMaxWidth/2;
	SnakeBody.y = _BoardMaxHeight/2;
	_TheSnake.push_back(SnakeBody);	
	_TheSnakeDirection = Snake::kRight;	
	_TheMouse = this->NewMousePosition();
		
	// Draw border once at startup
	DrawGrid();	

	_ItemsToDraw.push_back( {_TheSnake.back(), SNAKE_SYMBOOL} );
	_ItemsToDraw.push_back( {_TheMouse, MOUSE_SYMBOOL} );
	this->Draw();
}

Snake::~Snake()
{
	// do nothing
}

int Snake::Run()
{
	// Get user input (it works only for Win OS)
	if (GetAsyncKeyState(VK_ESCAPE) != 0)
    {
		// press ESC to force exit game
        return (-1);
    }
	if (GetAsyncKeyState(VK_UP) != 0)
    {
		if (_TheSnakeDirection != kDown)
		{
			_TheSnakeDirection = kUp;
		}        
    }
	if (GetAsyncKeyState(VK_RIGHT) != 0)
    {
		if (_TheSnakeDirection != kLeft)
		{
			_TheSnakeDirection = kRight;
		}        
    }
	if (GetAsyncKeyState(VK_DOWN) != 0)
    {
		if (_TheSnakeDirection != kUp)
		{
			_TheSnakeDirection = kDown;
		}        
    }
	if (GetAsyncKeyState(VK_LEFT) != 0)
    {
		if (_TheSnakeDirection != kRight)
		{
			_TheSnakeDirection = kLeft;
		}        
    }
	
	// Add new snake head
	TypePoint NextHead = _TheSnake.back();
	switch (_TheSnakeDirection)
	{
		case kUp:
			NextHead.y = MakePointYCircular(NextHead.y - 1);
			break;
		case kRight:
			NextHead.x = MakePointXCircular(NextHead.x + 1);
			break;
		case kDown:
			NextHead.y = MakePointYCircular(NextHead.y + 1);
			break;
		case kLeft:
			NextHead.x = MakePointXCircular(NextHead.x - 1);
			break;
		default:
			// ERR: not valid direction
			break;
	};	
	if (this->CheckCollision(NextHead) == true)
	{
		// game over
		std::cout << "  >>> Game Over! <<<\n";
		return -1;
	}
	_TheSnake.push_back(NextHead);
	_ItemsToDraw.push_back( {_TheSnake.back(), SNAKE_SYMBOOL} );

	// Eat the mouse
	if ( (NextHead.x == _TheMouse.x) && 
		 (NextHead.y == _TheMouse.y) )
	{	
		// Note: snake grows, but the tail is still on the same place
		// Place a new mouse
		_TheMouse = NewMousePosition();
		_ItemsToDraw.push_back( {_TheMouse, MOUSE_SYMBOOL} );
	}
	else
	{
		// Move tail by removing the old one
		_ItemsToDraw.push_back( {_TheSnake.front(), BLANK_SYMBOOL} );
		_TheSnake.pop_front();		
	}

	// check win
	if (_TheSnake.size() >= _MaxSnake)
	{
		std::cout << "  ^^^ YOU WIN :) ^^^\n";
		return 1;
	}

	// Update screen
	this->Draw();

	// Kind of game frame rate
	Sleep(500);
	return 0;
}

void Snake::Draw()
{
	for (const auto& item : _ItemsToDraw)
	{
		COORD Position = { item.pos.x, item.pos.y };
		SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Position);
    	std::cout << item.symbol;
	}
	_ItemsToDraw.clear();
	// Avoid "noisy" cursor by moving to the bottom-right corner
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), { _BoardMaxHeight, _BoardMaxWidth });
	std::cout << "+";
}

/* Private */

Snake::TypePoint Snake::NewMousePosition()
{
	bool FindPosition = true;
	TypePoint Position;

	// Note: hide a buggin' behavior because
	// it could takes a lot to find a valid 
	// position when the board is almost filled (!)

	while (FindPosition)
	{
		Position.x = rand() % _BoardMaxWidth;
		Position.y = rand() % _BoardMaxHeight;
		FindPosition = this->CheckCollision(Position);
	}
	return Position;
}

short Snake::MakePointXCircular(const short value)
{
	if (value < 0)
	{
		return (_BoardMaxWidth - 1);
	}
	else if (value >= _BoardMaxWidth)
	{
		return 0;
	}
	else
	{
		return (value);
	}
}

short Snake::MakePointYCircular(const short value)
{
	if (value < 0)
	{
		return (_BoardMaxHeight - 1);
	}
	else if (value >= _BoardMaxHeight)
	{
		return 0;
	}
	else
	{
		return (value);
	}
}

bool Snake::CheckCollision(const TypePoint target)
{
	bool Collided = false;
	for (const auto& body : _TheSnake)
	{
		if ((target.x == body.x) &&
			(target.y == body.y))
		{
			Collided = true;
			break;
		}
	}
	return Collided;
}

void Snake::DrawGrid()
{
	COORD Pos = {0, 0};
	for (short r = 0; r <= _BoardMaxHeight; r++)
	{
		Pos = { _BoardMaxWidth, r };
		SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		std::cout << "|";
	}
	for (short c = 0; c <= _BoardMaxWidth; c++)
	{
		Pos = { c, _BoardMaxHeight };
		SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		std::cout << "-";
	}
	// Draw board "limit angle"
    Pos = { _BoardMaxHeight, _BoardMaxWidth };
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
    std::cout << "+";
}