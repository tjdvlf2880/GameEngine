module;
export module App;

import WindowTask;
import IFrameTask;

export class App
{
	friend class AppTask;
public:
	App(IFrameTask* task);
	void Initialize();
	void Run();
	void Release();
private:
	bool brun;
	WindowTask windowTask;
	IFrameTask* frametask;
};
