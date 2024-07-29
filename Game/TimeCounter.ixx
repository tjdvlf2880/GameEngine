module;
#pragma once;
#include <chrono>
export module TimeCounter;

export class TimeCounter
{
public:
	void Reset();
	void Sleep(long miliseconds);
	double Update();
private:
	std::chrono::duration<double> tick;
	std::chrono::high_resolution_clock::time_point prev;
};
