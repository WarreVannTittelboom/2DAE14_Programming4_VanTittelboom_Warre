// Tron.cpp : This file contains the 'main' function. Program execution begins and ends there.

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include"TronGame.h"

int main(int, char* []) {
	dae::Minigin engine;
	engine.Initialize();
	dae::TronGame::GetInstance().CreateScenes();
	engine.Run();
	return 0;
}