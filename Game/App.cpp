module;
#pragma once
module App;
import DebugConsole;
bool App::Initialize()
{
	DebugConsole::Write(L"EngineInitialize\n");
	windowTask.Initialize();
	return true;
}

bool App::Run()
{
	DebugConsole::Write(L"EngineRun\n");
	AppRun = true;
	windowTask.Run();
	AppRun = false;
	return true;
}

bool App::Release()
{
	DebugConsole::Write(L"EngineRelease\n");
	windowTask.Release();
	return true;
}



