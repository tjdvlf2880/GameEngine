module;
#pragma once
module AppTask;

AppTask::AppTask()
{
	task.Create();
}

AppTask::~AppTask()
{
	task.Delete();
}

void AppTask::Initialize(IFrameTask* frametask)
{
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
}
