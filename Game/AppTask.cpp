module;
#pragma once
module AppTask;
import CrtReport;
void AppTask::Initialize(IFrameTask* frametask)
{
	task.Create(L"AppTask");
	task.SetTask([this , &frametask]()
		{
			app = new App(frametask);
			app->Initialize();
		});

	this->task.JoinTask();
}

void AppTask::Run()
{
	app->brun = true;
	task.SetTask([this]()
		{
			app->Run();
		});
}

void AppTask::Release()
{
	
	app->brun = false;
	task.SetTask([this]()
		{
			app->Release();
		});
	task.JoinTask();
	//CrtReport report;
	//report.MemCheckPoint();
	//report.Check();
	task.Delete();
	
}
