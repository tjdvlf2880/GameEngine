export module AppTask;
import MultiTask;
import App;

export class AppTask
{
private:
	MultiTask task;
	App* app;
public:
	void Initialize();
	void Run();
	void Release();
};

