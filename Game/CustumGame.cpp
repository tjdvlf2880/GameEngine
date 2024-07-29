module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
module CustumGame;
import DebugConsole;
void CustumGame::Initialize()
{
	elapsed_time = 0;
	brun = true;
	clock.Reset();
}

void CustumGame::Update()
{
	if (brun)
	{
		elapsed_time += clock.Update();
		double fps = fpsCounter.Count(NULL);
		if (elapsed_time >= 2)
		{
			DebugConsole::Write(L"Thread task : %d  , FPS : %f \n", GetCurrentThreadId() , fps);
			elapsed_time = 0; 
		}
	}
}

void CustumGame::Release()
{
	brun = false;
}
