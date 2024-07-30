module;
export module App;

import WindowTask;
export class App
{
	friend class AppTask;
public:
	void Initialize();
	void Run();
	void Release();
private:
	WindowTask windowTask;
};
