module;
#pragma once
module AppTask;
import CrtReport;
void AppTask::Initialize()
{
	task.Create(L"AppTask");
	task.SetTask([this]()
		{
			app = new App();
			app->Initialize();
		});
	task.JoinTask();
}

void AppTask::Run()
{
	task.SetTask([this]()
		{
			app->Run();
		});
}

void AppTask::Release()
{
	task.SetTask([this]()
		{
			app->Release();
			delete app;
		});
	task.Delete();
}
