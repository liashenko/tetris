#pragma once

class Tetramino
{
public:
	Tetramino(void);
	Tetramino(int shape, int x, int y, int angle);
	~Tetramino(void);
	bool GetValue(int x, int y) const;
	void Move (int dx, int dy);
	void SetSpeed(int speed);
	int GetSpeed() const;
	void Rotate();
	int GetX() const;
	int GetY() const;
private:
	int shape;
	int angle;
	int speed;
	int x;
	int y;
};
