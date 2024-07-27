module;
#pragma once
module App;

bool App::Initialize()
{
	windowTask.Initialize();
	return true;
}

bool App::Run()
{
	AppRun = true;
	windowTask.Run();
	AppRun = false;
	return true;
}

bool App::Release()
{
	windowTask.Release();
	return true;
}



