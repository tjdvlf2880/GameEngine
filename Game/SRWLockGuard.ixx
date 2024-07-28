module;
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
export module SRWLockGuard;

export enum SRW_TYPE
{
	SHARED,
	EXCLUSIVE,
};

export template <SRW_TYPE Mode>
class SRWLockGuard
{
public:
	SRWLockGuard(SRWLOCK& lock) : _lock(lock)
	{
		if constexpr (Mode == SHARED)
		{

			AcquireSRWLockShared(&lock);
		}
		else
		{
			AcquireSRWLockExclusive(&lock);
		}
	}
	~SRWLockGuard()
	{
		if constexpr (Mode == SHARED)
		{
			ReleaseSRWLockShared(&_lock);
		}
		else
		{
			ReleaseSRWLockExclusive(&_lock);
		}
	}
private:
	SRWLOCK& _lock;
};