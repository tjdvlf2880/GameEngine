module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
export module Window;
import std;

export class Window
{
	friend class WindowTask;
	friend LRESULT WinMessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	std::wstring Regist_WindowName = L"GameWindow";
	void CheckErr();
	void Register_Window();
	void Create_Window();
	void Register_InputDevice();
	void UnRegister_InputDevice();
	void UnRegister_Window();
	void Show_Update();
	void MessageProc();
	void Destroy();
	HWND hwnd;
};