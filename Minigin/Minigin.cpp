#pragma once
#include "MiniginPCH.h"
#include "SDL_mixer.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Timer.h"
#include "TextureComp.h"
#include <iostream>
#include "ServiceLocator.h"

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Error: SDL_Mixer Init error";
	}


	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int(m_WindowSize.x),
		int(m_WindowSize.y),
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	ServiceLocator::GetInstance().RegisterSoundSystem(new dae::AudioSystem());
}

void dae::Minigin::Cleanup()
{
	ServiceLocator::GetInstance().ReleaseSoundSystem();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		auto lastTime = chrono::high_resolution_clock::now();
		bool doContinue = true;
		float lag = 0.0f;
		ServiceLocator::GetInstance().GetSoundSystem().Enqueue("../Data/theme.wav", -1,20);
		while (doContinue)
		{
			const auto currentTime = chrono::high_resolution_clock::now();
			float deltaTime = chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			Timer::GetInstance().Set(deltaTime);
			doContinue = input.ProcessInput();
			sceneManager.Update();
			while (lag >= m_FixedTimeStep)
			{
				sceneManager.FixedUpdate(m_FixedTimeStep);
				lag -= m_FixedTimeStep;
			}
			sceneManager.LateUpdate();
			renderer.Render();
			auto sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
		ServiceLocator::GetInstance().GetSoundSystem().StopQueue();
	}

	Cleanup();
}
