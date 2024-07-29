module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
export module DebugConsole;
import Singleton;
import std;

export class DebugConsole : public Singleton<DebugConsole>
{
private:
	static std::mutex mtx;
	static HANDLE hConsole;
public:
	DebugConsole();
	~DebugConsole();
	static void Write(std::wstring format , ...);

};