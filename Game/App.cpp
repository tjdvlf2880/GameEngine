module;
#pragma once
module App;
import DebugConsole;
import Input;


void App::Initialize()
{
	DebugConsole::Write(L"EngineInitialize\n");
	Input::AddRef();
	windowTask.Initialize();
}

void App::Run()
{
	windowTask.Run();
}

void App::Release()
{
	DebugConsole::Write(L"EngineRelease\n");
	windowTask.Release();
	Input::Release();
}