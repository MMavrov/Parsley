#include<windows.h>
#include "Engine.h"

int wWinMain(HINSTANCE hInst, HINSTANCE prevInst, LPWSTR szCmdLine, int nCmdShow)
{
	Engine engine;
	engine.Run();
	return 0;
}