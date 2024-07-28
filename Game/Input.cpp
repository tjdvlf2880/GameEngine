module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
module Input;

Input* Input::instance = nullptr;

Input::Input()
{
	instance = nullptr;
}

Input* Input::GetInst()
{
	if (instance == nullptr)
	{
		instance = new Input();
	}
	return instance;
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

void Input::Bindkey(unsigned short logicKey, unsigned short vkey)
{
	keys[logicKey] = vkey;
}

void Input::UpdateKeyState(unsigned short vkey, unsigned short message)
{

}

Input::~Input()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
