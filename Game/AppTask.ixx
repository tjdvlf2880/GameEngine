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
	void Initialize(IFrameTask* task);
	void Run();
	void Release();
};

