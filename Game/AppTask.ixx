export module AppTask;
import MultiTask;
import App;
import IFrameTask;
export class AppTask
{
private:
	MultiTask task;
	App* app;
public:
	AppTask();
	~AppTask();
	void Initialize(IFrameTask* task);
	void Run();
	void Release();
};

