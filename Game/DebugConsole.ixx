module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
export module DebugConsole;
import std;

export class DebugConsole
{
private:
	DebugConsole();
	static HANDLE hConsole;
	static HANDLE GetConsole();
	static std::mutex mtx;
public:
	~DebugConsole();
	static void Write(std::wstring format , ...);
};