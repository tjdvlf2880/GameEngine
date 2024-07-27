module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <crtdbg.h>
#include <Windows.h>
export module Main;
import App;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
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