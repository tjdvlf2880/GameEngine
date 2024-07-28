module;
#pragma once
module App;
import DebugConsole;
App::App(IFrameTask* task)
	:frametask(task)
{

}

void App::Initialize()
{
	DebugConsole::Write(L"EngineInitialize\n");
	windowTask.Initialize();
	frametask->Initialize();
}

void App::Run()
{
	DebugConsole::Write(L"EngineRun\n");
	windowTask.Run();
	while (brun)
	{
		frametask->Update();
	}
}

void App::Release()
{
	DebugConsole::Write(L"EngineRelease\n");
	frametask->Release();
	windowTask.Release();
}