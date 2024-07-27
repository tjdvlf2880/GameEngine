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
	//Write�� ���� ȣ������� ���� ���ؽ��� ���� ������ �������ϴ�.
	if (hConsole == nullptr)
	{
		AllocConsole();
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		/*
			�ܼ� â�� ������ ���μ����� ���� ����ȴ�.
			�̴� �޸� ������ �߻��� ������ �������� �ݱ� ��ư�� ��Ȱ��ȭ�ص���.
		*/
		HWND consoleWindow = GetConsoleWindow();
		HMENU hmenu = GetSystemMenu(consoleWindow, FALSE);
		DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
	}
	return hConsole;
}

