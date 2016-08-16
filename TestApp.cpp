// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"

TestApp::TestApp() : Parent(200, 180)
{
	tetramino = Tetramino(rand() % 5, 8, 1, 0);
	nextTetramino = Tetramino(rand() % 5, 8, 1, 0);
	filledArea = FilledArea();
	//������������� ��������
	counter = 1000;
}

void TestApp::DrawFilledArea()
{
	//������� ����������� ������� �� �����������
	for(int j = 0; j < FilledArea::WIDTH + 2; j++)
	{
		SetChar(j * 1, 0, '#');
		SetChar(j * 1, (FilledArea::HEIGHT + 1), '#');
	}
	//������� ����������� ������� �� ���������
	for(int i = 0; i < FilledArea::HEIGHT + 2; i++)
	{
		SetChar(0, i * 1, '#');
		SetChar((FilledArea::WIDTH + 1), i * 1, '#');
	}
	//��������� ����������� �������
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
	
	//��������� ������
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
	//������� ������� ��������� ��������� ������ �� �����������
	for(int j = FilledArea::WIDTH + 2; j < FilledArea::WIDTH + 9; j++)
	{
		SetChar(j * 1, 0, '#');
		SetChar(j * 1, 5, '#');
	}
	//������� ������� ��������� ��������� ������ �� ���������
	for(int i = 0; i < 5; i++)
	{
		SetChar(FilledArea::WIDTH + 8, i*1, '#');
	}
	//������ ���� ������� ��������� ��������� ������
	for(int i = 1; i < 5; i++)
	{
		for(int j = FilledArea::WIDTH + 2; j < FilledArea::WIDTH + 8; j++)
		{
			SetChar(j*1, i*1, '.');
		}
	}
	//��������� ��������� ������
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
	//��������� ����������� �������
	DrawFilledArea();
	//��������� ������� ������
	DrawTetramino();
	//��������� ��������� ������
	DrawNextTetramino();
}

void TestApp::Turn()
{
	//������� ������ ����
	Tetramino t = tetramino;
	t.Move(0, 1);
	//������ ����������� � ����������� ��������
	if(filledArea.IsCollision(t) == false)
	{
		tetramino = t;
	}
	else
	{
		//�������� ������ � ����������� �������
		filledArea.Merge(tetramino);
		//������� �������� �����
		filledArea.RemoveSolidLines();
		//����� ������
		tetramino = nextTetramino;
		nextTetramino = Tetramino(rand() % 5, 8, 1, 0);
		//���� ����� ������ �������� ����������� ������� - �������� ����
		if(filledArea.IsCollision(tetramino))
		{
			filledArea.Refresh();
		}
	}
}

void TestApp::UpdateF(float deltaTime)
{
	//��������� ������
	Draw();
	//�������� ����
	if (counter > DELAY / tetramino.GetSpeed())
	{
		counter = 0;
		//���
		Turn();
	}
	counter++;
}
