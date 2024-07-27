export module App;
import WindowTask;

export class App
{
public:
	bool Initialize();
	bool Run();
	bool Release();
private:
	WindowTask windowTask;
	bool AppRun;
};
