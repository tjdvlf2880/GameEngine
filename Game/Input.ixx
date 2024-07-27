module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>
export module Input;
import std;

export enum KeyState {
	NONE = 0b00,        // 00: �Է� ����
	DOWN = 0b01,		// 01: ����
	PRESS = 0b11,       // 11: ������ ��
	RELEASE = 0b10      // 10: ��
};

struct InputMessage
{
	unsigned short vKey;
	unsigned int message;
};

export class Input
{
private:
	Input();
	static Input* instance;
	static std::unordered_map<uint8_t, KeyState> keyStates;
public:
	~Input();
	static Input* GetInst();
	std::wstring GetVkeyName(unsigned int vkey);
};

