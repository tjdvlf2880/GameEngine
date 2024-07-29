#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
import CrtReport;
import CustumGame;
import std;
import DebugConsole;
import AppTask;
import Input;
#define Main_Console

#ifdef Main_Console
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
int main()
#else
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
#endif
{
	DebugConsole::Create();
	CrtReport report;
	CustumGame game;
	{
		Input::GetInst()->Create();
		AppTask app;
		app.Initialize(&game);
		app.Run();
		app.Release();
		Input::GetInst()->Delete();
	}
	report.Check(DumpMode::Conosle);
	DebugConsole::GetInst()->Delete();
	report.FinalCheck(DumpMode::VsOutput);
	return 0;
}