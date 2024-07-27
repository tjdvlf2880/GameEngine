#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include <crtdbg.h>
#include <hidusage.h>
#include <thread>
import App;
int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG
	App app;
	app.Initialize();
	app.Run();
	app.Release();
	return 0;
}