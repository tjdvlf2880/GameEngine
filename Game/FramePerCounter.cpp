module;
#pragma once;
#include <chrono>
#include <thread>
module FramePerCounter;

FramePerCounter::FramePerCounter()
	: frame_count(0),fps(0), start_time(std::chrono::high_resolution_clock::now())
{

}

double FramePerCounter::Count(int maxfps)
{
	if (maxfps)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((long)(1000.0 / maxfps)));
	}
	frame_count++;
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - start_time;
	if (elapsed_seconds.count() >= 1.0) {
		fps = frame_count / elapsed_seconds.count();
		frame_count = 0;
		start_time = now;
	}
	return fps;
}