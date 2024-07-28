module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <hidusage.h>
#include <windowsx.h>
module WindowTask;
import DebugConsole;
import Input;

LRESULT WinMessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		POINT pos;
		pos.x = GET_X_LPARAM(lParam);
		pos.y = GET_Y_LPARAM(lParam);
		break;
	case WM_INPUT:
	{
		UINT dwSize = sizeof(RAWINPUT);
		static BYTE lpb[sizeof(RAWINPUT)];
		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
		RAWINPUT* raw = (RAWINPUT*)lpb;
		if (raw->header.dwType == RIM_TYPEKEYBOARD)
		{
			DebugConsole::Write(TEXT("%s : %d\n"), Input::GetInst()->GetVkeyName(raw->data.keyboard.VKey).c_str(), raw->data.keyboard.Flags);
			(raw->data.keyboard.VKey, raw->data.keyboard.Message);
		}
		else if (raw->header.dwType == RIM_TYPEMOUSE)
		{
			RAWMOUSE& mouse = raw->data.mouse;
			POINT relative;
			relative.x = mouse.lLastX;
			relative.y = mouse.lLastY;
			switch (mouse.usButtonFlags)
			{
			case RI_MOUSE_LEFT_BUTTON_DOWN:
				DebugConsole::Write(L"RI_MOUSE_LEFT_BUTTON_DOWN\n");
				break;
			case RI_MOUSE_LEFT_BUTTON_UP:
				DebugConsole::Write(L"RI_MOUSE_LEFT_BUTTON_UP\n");
				break;
			case RI_MOUSE_RIGHT_BUTTON_DOWN:
				DebugConsole::Write(L"RI_MOUSE_RIGHT_BUTTON_DOWN\n");
				break;
			case RI_MOUSE_RIGHT_BUTTON_UP:
				DebugConsole::Write(L"RI_MOUSE_RIGHT_BUTTON_UP\n");
				break;
			case RI_MOUSE_WHEEL:
			{
				float wheelDelta = (float)(short)mouse.usButtonData;
				float scrollDelta = wheelDelta / WHEEL_DELTA;
				unsigned long scrollLines;
				SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &scrollLines, 0);
				scrollDelta *= scrollLines;
				if (scrollDelta != 0)
				{
					DebugConsole::Write(L"RI_MOUSE_MIDDLE_BUTTON_UP %f\n", scrollDelta);
				}
				break;
			}
			}
		}
		break;
	}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void Window::CheckErr()
{
#ifdef _DEBUG
	DWORD error = GetLastError();
	LPTSTR errorMsg = nullptr;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&errorMsg, 0, NULL);
	DebugConsole::Write(errorMsg);
	LocalFree(errorMsg);
#endif // _DEBUG
}

void Window::Register_Window()
{
	WNDCLASSEX prop = { 0 };
	prop.cbSize = sizeof(WNDCLASSEX);
	prop.style = CS_HREDRAW | CS_VREDRAW;
	prop.lpfnWndProc = WinMessageProc;
	prop.cbClsExtra = 0;
	prop.cbWndExtra = 0;
	prop.hInstance = GetModuleHandleW(NULL);
	prop.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	prop.hCursor = LoadCursor(NULL, IDC_ARROW);
	prop.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	prop.lpszMenuName = NULL;
	prop.lpszClassName = Regist_WindowName.c_str();
	prop.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&prop))
	{
		CheckErr();
	}
}

void Window::Create_Window()
{
	hwnd = CreateWindowEx(NULL, Regist_WindowName.c_str(), NULL, WS_OVERLAPPED | WS_SIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, GetModuleHandleW(NULL), NULL);
	if (hwnd == NULL)
	{
		CheckErr();
	}
}

void Window::Register_InputDevice()
{
	RAWINPUTDEVICE Rid[2] = { 0 };
	// adds HID mouse and also ignores legacy mouse messages
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	Rid[0].dwFlags = NULL;
	Rid[0].hwndTarget = hwnd;
	// adds HID keyboard and also ignores legacy keyboard messages
	Rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD;
	Rid[1].dwFlags = RIDEV_NOLEGACY;
	Rid[1].hwndTarget = hwnd;
	if (!RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])))
	{
		CheckErr();
	}
}


void Window::UnRegister_InputDevice()
{
	RAWINPUTDEVICE Rid[2] = { 0 };
	// adds HID mouse and also ignores legacy mouse messages
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	Rid[0].dwFlags = RIDEV_REMOVE;
	Rid[0].hwndTarget = hwnd;
	// adds HID keyboard and also ignores legacy keyboard messages
	Rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD;
	Rid[1].dwFlags = RIDEV_REMOVE;
	Rid[1].hwndTarget = hwnd;
	if (!RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])))
	{
		CheckErr();
	}
}

void Window::UnRegister_Window()
{
	if (!UnregisterClass(Regist_WindowName.c_str(), GetModuleHandleW(NULL)))
	{
		CheckErr();
	}
}

void Window::Show_Update()
{
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	//GetCursorPos(&pos);
}

void Window::MessageProc()
{
	MSG msg;
	BOOL bRet;

	while ((bRet = GetMessage(&msg, hwnd, 0, 0)) != 0)
	{
		if ((bRet == -1))
		{
			break;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void Window::Destroy()
{
	PostMessage(hwnd, WM_CLOSE, 0, 0);
}
