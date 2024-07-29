module;
#pragma once;
#include <chrono>
#include <thread>
module FramePerCounter;

FramePerCounter::FramePerCounter()
	: frame_count(0),fps(0), elapsed_seconds(0)
{
	clock.Reset();
}

double FramePerCounter::Count(int maxfps)
{
	if (maxfps)
	{
		clock.Sleep((long)(1000.0 / maxfps));
	}
	frame_count++;
	elapsed_seconds += clock.Update();
	if (elapsed_seconds >= 1.0) {
		fps = frame_count / elapsed_seconds;
		frame_count = 0;
		elapsed_seconds = 0;
	}
	return fps;
}