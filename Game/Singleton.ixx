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
    static int refCount;
protected:
    static SRWLOCK srwlock;
    Singleton() = default;
public:
    static T* GetInst();
    static T* AddRef();
    static void Release();
};
template <typename T>
T* Singleton<T>::instance = nullptr;

template <typename T>
int Singleton<T>::refCount = 0;

template <typename T>
SRWLOCK Singleton<T>::srwlock = SRWLOCK_INIT;

template<typename T>
T* Singleton<T>::GetInst()
{
    return instance;
}

template<typename T>
T* Singleton<T>::AddRef()
{
    SRWLockGuard<EXCLUSIVE> lock(srwlock);
    if (instance == nullptr)
    {
        instance = new T;
    }
    refCount++;
    return instance;
}

template<typename T>
void Singleton<T>::Release()
{
    SRWLockGuard<EXCLUSIVE> lock(srwlock);
    refCount--;
    if (refCount == 0)
    {
        delete instance;
        instance = nullptr;
    }
}