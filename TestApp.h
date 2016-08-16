// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"
#include "Tetramino.h"
#include "FilledArea.h"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		//текущая фигура
		Tetramino tetramino;
		//следующая фигура
		Tetramino nextTetramino;
		//заполненная область
		FilledArea filledArea;
		//счётчик для задержки
		int counter;
		//задержка
		static const int DELAY = 20;
	public:
		TestApp();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
		void Turn();
		void Draw();
		void DrawFilledArea();
		void DrawTetramino();	
		void DrawNextTetramino();
};
