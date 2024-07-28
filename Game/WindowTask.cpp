module;
#pragma once
module WindowTask;

WindowTask::WindowTask()
{
	task.Create();
}

WindowTask::~WindowTask()
{
	task.Delete();
}

void WindowTask::Initialize()
{
	task.SetTask([this]()
		{
			window.Register_Window();
			window.Create_Window();
			window.Register_InputDevice();
		});
	task.JoinTask();
}

void WindowTask::Run()
{
	task.SetTask([this]()
		{
			window.Show_Update();
			window.MessageProc();
		});
}

void WindowTask::Release()
{
	window.Destroy();
	task.SetTask([this]()
		{
			window.UnRegister_InputDevice();
			window.UnRegister_Window();
		});
}
