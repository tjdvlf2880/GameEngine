module;
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wchar.h>
module DebugConsole;
import std;

HANDLE DebugConsole::hConsole = nullptr;
std::mutex DebugConsole::mtx;

DebugConsole::DebugConsole()
{
	hConsole = nullptr;
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
			std::lock_guard<std::mutex> lock(DebugConsole::mtx);
			WriteConsole(GetConsole(), buffer, wcslen(buffer), &bytesWritten, NULL);
		}
	}
#endif
}
void DebugConsole::Show()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}
void DebugConsole::Hide()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}
HANDLE DebugConsole::GetConsole()
{
	//Write에 의해 호출됨으로 상위 뮤텍스에 의해 스레드 세이프하다.
	if (hConsole == nullptr)
	{
		AllocConsole();
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		/*
			콘솔 창을 닫으면 프로세스가 강제 종료된다.
			이는 메모리 누수가 발생할 위험이 있음으로 닫기 버튼을 비활성화해두자.
		*/
		HWND consoleWindow = GetConsoleWindow();
		HMENU hmenu = GetSystemMenu(consoleWindow, FALSE);
		DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
	}
	return hConsole;
}

