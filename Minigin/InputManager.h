#pragma once
#include "Singleton.h"
#include <memory>
#include <map>
#include "Command.h"
#include <XInput.h>
#include "ControllerInput.h"
#include <Vector>

class Command;

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		explicit InputManager();
		~InputManager();
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) noexcept = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) noexcept = delete;

		bool ProcessInput();
		
		void AddCommand(std::map<SDL_Scancode, std::shared_ptr<Command>> &inputCommands, unsigned int id);
		void AddCommand(std::map<dae::controlButton,std::shared_ptr<Command>>& inputCommands, unsigned int id);

	
	private:
		using KeyBoardKey = std::pair<unsigned, SDL_Scancode>;
		using KeyBoardCommandsMap = std::map<KeyBoardKey, std::vector <std::shared_ptr<Command>>>;
		KeyBoardCommandsMap m_KeyboardCommands{};
		
		ControllerInput* m_pController;
		bool GetControllerInput(std::vector < std::pair <dae::controlInput , std::shared_ptr<Command >> > & commands) const;

	};

}
