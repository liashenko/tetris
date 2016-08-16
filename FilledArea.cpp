#include "FilledArea.h"

FilledArea::FilledArea(void)
{
	Refresh();
}

FilledArea::~FilledArea(void)
{
}
//очищаем заполненную область
void FilledArea::Refresh()
{
	for(int i = 0; i < FilledArea::HEIGHT; i++)
	{
		for(int j = 0; j < FilledArea::WIDTH; j++)
		{
			map[i][j] = false;
		}
	}	
	//нижняя строка заполняется true для обнаружения столкновения фигуры с низом заполненной области
	for(int j = 0;j < FilledArea::WIDTH; j++)
	{
		map[FilledArea::HEIGHT][j] = true;
	}
}

bool FilledArea::GetValue(int x, int y) const
{
	return map[y][x];
}

bool FilledArea::IsCollision (Tetramino &t) const
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if (t.GetValue(j, i) == true)
			{
				int x = t.GetX() + j - 1;
				int y = t.GetY() + i;
				if(x < 0 || x >= FilledArea::WIDTH || y < 0 || y >= FilledArea::HEIGHT)
					return true;
				if (t.GetValue(j, i) == map[y][x])
					return true;
			}
		}
	}
	return false;
}

void FilledArea::Merge(Tetramino &t)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(t.GetValue(j, i) == true)
			{
				int x = t.GetX() + j - 1;
				int y = t.GetY() + i;
				if(x >= 0 || x < FilledArea::WIDTH || y >= 0 || y < FilledArea::HEIGHT)
					map[y][x] = map[y][x] | t.GetValue(j, i);
			}
		}
	}
}

void FilledArea::RemoveSolidLines()
{
	for(int i = 0; i < FilledArea::HEIGHT; i++)
	{
		bool solid = true;
		for(int j = 0; j < FilledArea::WIDTH; j++)
		{
			solid &= map[i][j];
		}
		if(solid == true)
		{
			RemoveSolidLine(i);
		}
	}
}

void FilledArea::RemoveSolidLine(int k)
{
	//опускаем строки заполненной области
	for(int i = k - 1; i >= 0; i--)
	{
		for(int j = 0; j < FilledArea::WIDTH; j++)
		{
			map[i + 1][j] = map[i][j];
		}
	}
	//очищаем первую строку заполненной области
	for(int j = 0; j < FilledArea::WIDTH; j++)
	{
		map[0][j] = false;
	}

}

