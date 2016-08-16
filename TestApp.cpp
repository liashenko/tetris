// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"

TestApp::TestApp() : Parent(200, 180)
{
	tetramino = Tetramino(rand() % 5, 8, 1, 0);
	nextTetramino = Tetramino(rand() % 5, 8, 1, 0);
	filledArea = FilledArea();
	//инициилизация счётчика
	counter = 1000;
}

void TestApp::DrawFilledArea()
{
	//границы заполненной области по горизонтали
	for(int j = 0; j < FilledArea::WIDTH + 2; j++)
	{
		SetChar(j * 1, 0, '#');
		SetChar(j * 1, (FilledArea::HEIGHT + 1), '#');
	}
	//границы заполненной области по вертикали
	for(int i = 0; i < FilledArea::HEIGHT + 2; i++)
	{
		SetChar(0, i * 1, '#');
		SetChar((FilledArea::WIDTH + 1), i * 1, '#');
	}
	//отрисовка заполненной области
	for(int i = 1; i <= FilledArea::HEIGHT; i++)
	{
		for(int j = 1; j <= FilledArea::WIDTH; j++)
		{
			if(filledArea.GetValue(j - 1, i - 1) == true)
			{
				SetChar(j * 1, i * 1, '*');
			}
			else
			{
				SetChar(j * 1, i * 1, '.');
			}
		}
	}
}

void TestApp::DrawTetramino()
{
	int x = tetramino.GetX();
	int y = tetramino.GetY();
	
	//отрисовка фигуры
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(tetramino.GetValue(j, i) == true)
			{
				SetChar((x + j) * 1, (y + i) * 1, '*');
			}
		}
	}
}

void TestApp::DrawNextTetramino()
{
	//границы области подсказки следующей фигуры по горизонтали
	for(int j = FilledArea::WIDTH + 2; j < FilledArea::WIDTH + 9; j++)
	{
		SetChar(j * 1, 0, '#');
		SetChar(j * 1, 5, '#');
	}
	//границы области подсказки следующей фигуры по вертикали
	for(int i = 0; i < 5; i++)
	{
		SetChar(FilledArea::WIDTH + 8, i*1, '#');
	}
	//пустые поля области подсказки следующей фигуры
	for(int i = 1; i < 5; i++)
	{
		for(int j = FilledArea::WIDTH + 2; j < FilledArea::WIDTH + 8; j++)
		{
			SetChar(j*1, i*1, '.');
		}
	}
	//отрисовка следующей фигуры
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(nextTetramino.GetValue(j, i) == true)
			{
				SetChar((j + FilledArea::WIDTH + 3) * 1, (i + 2) * 1, '*');		
			}
		}
	}

}

void TestApp::KeyPressed(int btnCode)
{ 
	Tetramino t = tetramino;
	if (btnCode == 75)//left
	{ 
		t.Move(-1, 0);	
	}
	else if (btnCode == 77)//right
	{ 
		t.Move(1, 0);
	}
	else if (btnCode == 80)//down
	{ 
		t.SetSpeed(DELAY);
	}
	else if(btnCode == 32)//space
	{
		t.Rotate(); 
	}
	if(filledArea.IsCollision(t) == false)
	{
		tetramino = t;
		DrawFilledArea();
		DrawTetramino();
	}
}

void TestApp::Draw()
{
	//отрисовка заполненной области
	DrawFilledArea();
	//отрисовка текущей фигуры
	DrawTetramino();
	//отрисовка следующей фигуры
	DrawNextTetramino();
}

void TestApp::Turn()
{
	//текущую фигуру вниз
	Tetramino t = tetramino;
	t.Move(0, 1);
	//фигура столкнулась с заполненной областью
	if(filledArea.IsCollision(t) == false)
	{
		tetramino = t;
	}
	else
	{
		//добавить фигуру к заполненной области
		filledArea.Merge(tetramino);
		//удалить сплошные линии
		filledArea.RemoveSolidLines();
		//новая фигура
		tetramino = nextTetramino;
		nextTetramino = Tetramino(rand() % 5, 8, 1, 0);
		//если новая фигура касается заполненной области - обновить игру
		if(filledArea.IsCollision(tetramino))
		{
			filledArea.Refresh();
		}
	}
}

void TestApp::UpdateF(float deltaTime)
{
	//отрисовка экрана
	Draw();
	//задержка хода
	if (counter > DELAY / tetramino.GetSpeed())
	{
		counter = 0;
		//ход
		Turn();
	}
	counter++;
}
