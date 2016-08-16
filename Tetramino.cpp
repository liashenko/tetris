#include "Tetramino.h"

Tetramino::Tetramino(void)
{
}

Tetramino::~Tetramino(void)
{
}

Tetramino::Tetramino(int shape, int x, int y, int angle)
{
	this->shape = shape;
	this->x = x;
	this->y = y;
	this->angle = angle;
	this->speed = 1;
}

int Tetramino::GetSpeed() const
{
	return this->speed;
}

void Tetramino::SetSpeed(int speed)
{
	this->speed = speed;
}

int Tetramino::GetX() const
{
	return this->x;
}

int Tetramino::GetY() const
{
	return this->y;
}

void Tetramino::Rotate()
{
	this->angle = (this->angle + 1) % 4;
}

void Tetramino::Move (int dx, int dy)
{
	this->x += dx;
	this->y += dy;
}

bool Tetramino::GetValue(int x, int y) const 
{
	static const bool SHAPES[5][4][4][4] = 
	{
		{
			{
				{0, 0, 0, 0},
				{1, 1, 1, 1},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0}
			},
			{
				{0, 0, 0, 0},
				{1, 1, 1, 1},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0}
			}
		},
		{
			{
				{0, 1, 1, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{0, 1, 1, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{0, 1, 1, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{0, 1, 1, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			}
		},
		{
			{
				{1, 0, 0, 0},
				{1, 0, 0, 0},
				{1, 1, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{1, 1, 1, 0},
				{1, 0, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{0, 1, 1, 0},
				{0, 0, 1, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 0}
			},
			{
				{0, 0, 0, 0},
				{0, 0, 1, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0}
			}
		},
		{
			{
				{0, 0, 1, 1},
				{1, 1, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{0, 1, 0, 0},
				{0, 1, 1, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 0}
			},
				{
				{0, 0, 1, 1},
				{1, 1, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{0, 1, 0, 0},
				{0, 1, 1, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 0}
			}
		},
		{
			{
				{0, 1, 0, 0},
				{1, 1, 1, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{1, 0, 0, 0},
				{1, 1, 0, 0},
				{1, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{1, 1, 1, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{0, 1, 0, 0},
				{1, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 0, 0}
			}
		}
	};	
	return SHAPES[this->shape][angle][y][x];
}