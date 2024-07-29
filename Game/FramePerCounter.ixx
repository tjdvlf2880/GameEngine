module;
#pragma once;
#include <chrono>
export module FramePerCounter;
import TimeCounter;

export class FramePerCounter
{
public:
    FramePerCounter();
    double Count(int maxfps);
private:
    int frame_count;
    float fps;
    double elapsed_seconds;
    TimeCounter clock;
};
