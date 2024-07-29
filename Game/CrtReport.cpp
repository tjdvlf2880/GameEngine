module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <crtdbg.h>
module CrtReport;

import DebugConsole;
import StrConverter;

int __cdecl CustomReportHook(int reportType, char* message, int* returnValue)
{
	DebugConsole::Write(StringToWString(message).c_str());
	return true;
}

void CrtReport::SetMode(DumpMode mode)
{
	if (mode == Conosle)
	{
		_CrtSetReportHook(CustomReportHook);
	}
	else if (mode == VsOutput)
	{
		_CrtSetReportHook(nullptr);
	}
}

void CrtReport::MemCheckPoint()
{
	_CrtMemCheckpoint(&initialState);
}

void CrtReport::Check(DumpMode mode)
{
	_CrtMemState currentState;
	_CrtMemState diffState;
	_CrtMemCheckpoint(&currentState);
	if (_CrtMemDifference(&diffState, &initialState, &currentState))
	{
		SetMode(mode);
		_CrtMemDumpStatistics(&diffState);
	}
}


void CrtReport::FinalCheck(DumpMode mode)
{
	SetMode(mode);
	_CrtDumpMemoryLeaks();
}


CrtReport::CrtReport()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
#endif // _DEBUG
	MemCheckPoint();
}

