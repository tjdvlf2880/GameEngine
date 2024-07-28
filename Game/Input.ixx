module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>
export module Input;
import std;


export class Input
{
private:
	Input();
	static Input* instance;
public:
	~Input();
	static Input* GetInst();
	std::wstring GetVkeyName(unsigned short vkey);
	void Update();
};

