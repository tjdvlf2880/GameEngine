#pragma once
#define WIN32_LEAN_AND_MEAN
#include <crtdbg.h>
import AppTask;
import CustumGame;
int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	AppTask app[2];
	CustumGame mygame[2];
	for (int i = 0; i < 2; i++)
	{
		app[i].Initialize(&mygame[i]);
		app[i].Run();
		//app[i].Release();
	}
	return 0;
}