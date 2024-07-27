module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>
#include <Windows.h>
export module Window;

export class Window
{
public:
	friend class WindowTask;
private:
	std::wstring Regist_WindowName = L"GameWindow";
	static LRESULT MessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
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