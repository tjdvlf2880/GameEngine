module;
#pragma once
export module CustumGame;
import IFrameTask;
import FramePerCounter;

export class CustumGame : public IFrameTask
{
	FramePerCounter fps;
	bool brun;
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
};
