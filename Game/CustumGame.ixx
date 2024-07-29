module;
#pragma once
export module CustumGame;
import IFrameTask;
import FramePerCounter;
import TimeCounter;
export class CustumGame : public IFrameTask
{
	TimeCounter clock;
	FramePerCounter fpsCounter;
	bool brun;
	float elapsed_time;
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
};
