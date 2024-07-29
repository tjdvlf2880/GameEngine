module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include <hidusage.h>
module Input;
import SRWLockGuard;
import DebugConsole;

Input::Input()
{
	RefCount = 0;
}

std::wstring Input::GetVkeyName(unsigned short vkey)
{
	TCHAR keyName[256] = { 0 };
	UINT scanCode = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	// 확장 키 처리
	switch (vkey) {
	case VK_LEFT: case VK_RIGHT: case VK_UP: case VK_DOWN:
	case VK_PRIOR: case VK_NEXT: case VK_END: case VK_HOME:
	case VK_INSERT: case VK_DELETE: case VK_DIVIDE:
		scanCode |= 0x100;
	}
	if (GetKeyNameText(scanCode << 16, keyName, sizeof(keyName)) != 0) 
	{
		return keyName;
	}
	return L"???";
}

void Input::Update()
{
}


bool Input::RegisterRawInput(HWND hwnd)
{
	SRWLockGuard<EXCLUSIVE> lock(srwlock);
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
	bool hr = RegisterRawInputDevices(Rid, 2, sizeof(Rid[0]));
	if (hr)
	{
		RefCount++;
		DebugConsole::Write(L"+InputDevice : %d \n" , RefCount);
	}
	return hr;
}

bool Input::UnRegisterRawInput()
{
	SRWLockGuard<EXCLUSIVE> lock(srwlock);
	RefCount--;
	DebugConsole::Write(L"-InputDevice : %d\n", RefCount);
	if (RefCount)
	{
		return true;
	}
	RAWINPUTDEVICE Rid[2] = { 0 };
	// adds HID mouse and also ignores legacy mouse messages
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	Rid[0].dwFlags = RIDEV_REMOVE;
	Rid[0].hwndTarget = NULL;
	// adds HID keyboard and also ignores legacy keyboard messages
	Rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD;
	Rid[1].dwFlags = RIDEV_REMOVE;
	Rid[1].hwndTarget = NULL;
	bool hr = RegisterRawInputDevices(Rid, 2, sizeof(Rid[0]));
	if (hr)
	{
		DebugConsole::Write(L"RemoveALLInputDevice : %d \n", RefCount);
	}

	return hr;
}
