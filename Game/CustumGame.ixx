module;
#pragma once
export module CustumGame;
import FramePerCounter;
import TimeCounter;
export class CustumGame 
{
	TimeCounter clock;
	FramePerCounter fpsCounter;
	bool brun;
	float elapsed_time;
public:
	void Initialize();
	void Update();
	void Release();
};
