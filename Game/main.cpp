#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
import CrtReport;
import std;


import DebugConsole;
import AppTask;
import CustumGame;
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
	CrtReport report;
	DebugConsole::Create();
	report.MemCheckPoint();


	std::optional<std::thread> worker;
	int count;
	worker.emplace([&count]() { count++; });
	if (worker.has_value())
	{
		worker.value().join();
		worker.reset();
	}
	report.Check();

	{
		Input::GetInst()->Create();
		CustumGame game;
		AppTask app;
		app.Initialize(&game);
		app.Run();
		app.Release();
		Input::GetInst()->Delete();
	}
	report.Check(DumpMode::Conosle);
	DebugConsole::GetInst()->Delete();
	report.FinalCheck(DumpMode::Conosle);
	return 0;
}