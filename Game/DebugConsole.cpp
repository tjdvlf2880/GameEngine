module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wchar.h>
module DebugConsole;
import std;

std::mutex DebugConsole::mtx;
HANDLE DebugConsole::hConsole = nullptr;

DebugConsole::DebugConsole()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == nullptr)
	{
		AllocConsole();
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	HWND consoleWindow = GetConsoleWindow();
	HMENU hmenu = GetSystemMenu(consoleWindow, FALSE);
	DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
}

DebugConsole::~DebugConsole()
{
	hConsole = nullptr;
	FreeConsole();
}

void DebugConsole::Write(std::wstring format, ...)
{
#ifdef _DEBUG
	DWORD bytesWritten = 0;
	{
		WCHAR buffer[1024];
		va_list args;
		va_start(args, format);
		_vsnwprintf_s(buffer, sizeof(buffer) / sizeof(WCHAR), format.c_str(), args);
		va_end(args);
		DWORD bytesWritten = 0;
		{
			std::lock_guard<std::mutex> lock(mtx);
			WriteConsole(DebugConsole::GetInst()->hConsole, buffer, wcslen(buffer), &bytesWritten, NULL);
		}
	}
#endif
}