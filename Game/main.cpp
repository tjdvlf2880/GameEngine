#pragma once
#define WIN32_LEAN_AND_MEAN
#include <crtdbg.h>
import AppTask;
import CustumGame;

import Window;

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	const int AppCount = 2;
	AppTask app[AppCount];
	CustumGame mygame[AppCount];
	for (int i = 0; i < AppCount; i++)
	{
		app[i].Initialize(&mygame[i]);
		app[i].Run();
		//app[i].Release();
	}
	return 0;
}