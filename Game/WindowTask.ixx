module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
export module WindowTask;
import MultiTask;
import Window;

export class WindowTask
{
private:
	MultiTask task;
	Window window;
public:
	void Initialize();
	void Run();
	void Release();
};

