module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
export module Singleton;

import SRWLockGuard;

export template<typename T>
class Singleton
{
private:
    static T* instance;
protected:
    static SRWLOCK srwlock;
    Singleton() = default;
public:
    static T* GetInst();
    static T* Create();
    static void Delete();
};
template <typename T>
T* Singleton<T>::instance = nullptr;

template <typename T>
SRWLOCK Singleton<T>::srwlock = SRWLOCK_INIT;

template<typename T>
T* Singleton<T>::GetInst()
{
    return instance;
}

template<typename T>
T* Singleton<T>::Create()
{
    if (instance == nullptr)
    {
        SRWLockGuard<EXCLUSIVE> lock(srwlock);
        if (instance == nullptr)
        {
            instance = new T;
        }
    }
    return instance;
}

template<typename T>
void Singleton<T>::Delete()
{
    SRWLockGuard<EXCLUSIVE> lock(srwlock);
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}