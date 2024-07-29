module;
#pragma once;
#include <chrono>
#include <thread>
module TimeCounter;


void TimeCounter::Reset()
{
	prev = std::chrono::high_resolution_clock::now();
}

void TimeCounter::Sleep(long miliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
}

double TimeCounter::Update()
{
	auto now = std::chrono::high_resolution_clock::now();
	tick  = now - prev;
	prev = now;
	return tick.count();
}

