module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
module CustumGame;
import DebugConsole;
void CustumGame::Initialize()
{
	DebugConsole::Write(L"CustumGame Initialize\n");
	elapsed_time = 0;
	clock.Reset();
}

void CustumGame::Update()
{
	elapsed_time += clock.Update();
	double fps = fpsCounter.Count(NULL);
	DebugConsole::Write(L"Thread task : %d  , time : %f \n", GetCurrentThreadId(), elapsed_time);
	if (elapsed_time >= 5)
	{
		DebugConsole::Write(L"Thread task : %d  , FPS : %f \n", GetCurrentThreadId(), fps);
		elapsed_time = 0;
	}
}

void CustumGame::Release()
{
	DebugConsole::Write(L"CustumGame Release\n");
}
