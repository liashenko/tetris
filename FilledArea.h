#pragma once

#include "Tetramino.h";

class FilledArea
{
public:
	enum {HEIGHT = 20, WIDTH = 15};
	FilledArea(void);
	~FilledArea(void);
	bool GetValue(int x, int y) const;
	bool IsCollision (Tetramino &t) const;
	void Merge(Tetramino &t);
	void RemoveSolidLines();
	void RemoveSolidLine(int k);
	void Refresh();
private:
	bool map[HEIGHT + 2][WIDTH];
};
