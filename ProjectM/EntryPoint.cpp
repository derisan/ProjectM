#include "pch.h"
#include "Engine.h"
#include "Application.h"

_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	Engine engine(1280, 720, L"Hello, world!");
	return Application::Run(&engine, hInstance, nCmdShow);
}
