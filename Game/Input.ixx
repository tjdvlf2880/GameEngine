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
	std::unordered_map<unsigned short, unsigned short> keys;
public:
	~Input();
	static Input* GetInst();
	std::wstring GetVkeyName(unsigned short vkey);
	void Bindkey(unsigned short logicKey, unsigned short vkey);
	void UpdateKeyState(unsigned short vkey, unsigned short message);
};

