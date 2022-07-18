#pragma once
#include "MiniginPCH.h"
struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void Run();
		void Cleanup();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		float m_FixedTimeStep = 0.02f;
		const glm::vec2 m_WindowSize{ 640,480 };
		SDL_Window* m_Window{};
	};
}