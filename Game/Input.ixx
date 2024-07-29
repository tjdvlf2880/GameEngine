module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
export module Input;
import std;
import Singleton;

export class Input : public Singleton<Input>
{
private:
	int RefCount;
public:
	Input();
	std::wstring GetVkeyName(unsigned short vkey);
	void Update();
	bool RegisterRawInput(HWND hwnd);
	bool UnRegisterRawInput();
};

