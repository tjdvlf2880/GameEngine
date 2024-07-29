module;
#pragma once
module WindowTask;

void WindowTask::Initialize()
{
	task.Create(L"WindowTask");
	task.SetTask([this]()
		{
			window.Register_Window();
			window.Create_Window();
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
			window.UnRegister_Window();
		});
	task.Delete();
}
