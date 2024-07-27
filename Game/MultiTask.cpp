module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
module MultiTask;

MultiTask::MultiTask()
{
	task = nullptr;
	thread_sem = CreateSemaphoreEx(NULL, 0, 1, NULL, NULL, SEMAPHORE_ALL_ACCESS);
	task_sem = CreateSemaphoreEx(NULL, 0, 1, NULL, NULL, SEMAPHORE_ALL_ACCESS);
}

MultiTask::~MultiTask()
{
	CloseHandle(task_sem);
	CloseHandle(thread_sem);
}

void MultiTask::SetTask(std::function<void()> func)
{
	JoinTask();
	if(func != nullptr)
	{
		task = func;
		ReleaseSemaphore(thread_sem, 1, 0);
	}
}

void MultiTask::Create()
{
	run = true;
	worker.emplace([this]()
		{
			while (true)
			{
				WaitForSingleObject(thread_sem, INFINITE);
				if (!run)
				{
					break;
				}
				else
				{
					task();
					ReleaseSemaphore(task_sem, 1, 0);
				}
			}
		});
}

void MultiTask::JoinTask()
{
	if (task != nullptr)
	{
		WaitForSingleObject(task_sem, INFINITE);
		task = nullptr;
	}
}

void MultiTask::Delete()
{
	JoinTask();
	run = false;
	ReleaseSemaphore(thread_sem, 1, 0);
	worker.value().join();
	//worker.reset();
}
