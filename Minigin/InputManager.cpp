#include "MiniginPCH.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Command.h"
#include "imgui_impl_sdl.h"

dae::InputManager::InputManager()
{
	m_pController = new ControllerInput();
}

dae::InputManager::~InputManager()
{
	delete m_pController;
	m_pController = nullptr;
}

bool dae::InputManager::ProcessInput()
{
	std::vector<std::pair<dae::controlInput, std::shared_ptr<Command>>> commands{};

	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			//quits game loop (doContinue)
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			for (auto& k : m_KeyboardCommands)
			{
				if (e.key.keysym.scancode == k.first.second)
				{
					k.second->Execute();
				}
			}
		}
		if (e.type == SDL_KEYUP)
		{
			for (auto& k : m_KeyboardCommands)
			{
				if (e.key.keysym.scancode == k.first.second)
				{
					k.second->Release();
				}
			}
		}

		//mouse input ?


		//imgui input
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	
	if (GetControllerInput(commands))
	{
		for (const auto& c : commands)
		{
			if (c.first.isPressed)
			{
				c.second->Execute();
			}
			else
			{
				c.second->Release();
			}
		}
	}

	return true;
}


void dae::InputManager::AddCommand(std::map<SDL_Scancode, std::shared_ptr<Command>>& inputCommands, unsigned int id)
{
	for (auto& c : inputCommands)
	{
		m_KeyboardCommands[std::make_pair(id, c.first)] = std::move(c.second);
	}
}

void dae::InputManager::AddCommand(std::map<dae::controlButton, std::shared_ptr<Command>>& inputCommands, unsigned int id)
{
	m_pController->AddCommand(inputCommands, id);
}



bool dae::InputManager::GetControllerInput(std::vector<std::pair<dae::controlInput, std::shared_ptr<Command>>>& commands) const
{
	commands = m_pController->ProcessInput();
	if (commands.size() != 0) 
	{
		return true; 
	}
	
	return false;
}