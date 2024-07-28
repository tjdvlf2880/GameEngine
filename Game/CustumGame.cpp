module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
module CustumGame;
import DebugConsole;
void CustumGame::Initialize()
{
	brun = true;
}

void CustumGame::Update()
{
	if (brun)
	{
		DWORD threadId = GetCurrentThreadId();
		DebugConsole::Write(L"Thread task : %d  , FPS : %f \n", threadId , fps.Count(NULL) );
		//Do Somthing
	}
}

void CustumGame::Release()
{
	brun = false;
}
