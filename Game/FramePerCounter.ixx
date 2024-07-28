module;
#pragma once;
#include <chrono>
export module FramePerCounter;

export class FramePerCounter
{
public:
    FramePerCounter();
    double Count(int maxfps);
private:
    int frame_count;
    double fps;
    std::chrono::high_resolution_clock::time_point start_time;
};
