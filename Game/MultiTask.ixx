module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <functional>
#include <optional>
#include <Windows.h>
export module MultiTask;
import std;
export class MultiTask
{
public:
    void Create(std::wstring name = L"");
    void SetTask(std::function<void()> func);
    void JoinTask();
    void Delete();
private:
    std::wstring taskname;
    bool run;
    bool taskover;
    HANDLE thread_sem;
    HANDLE task_sem;
    std::function<void()> task;
    std::optional<std::thread> worker;
};

