export module IFrameTask;
export class IFrameTask
{
public:
	virtual void Initialize() abstract;
	virtual void Update() abstract;
	virtual void Release() abstract;
};