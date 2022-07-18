#include "MiniginPCH.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment (lib, "xinput.lib")
#include "Command.h"
#include <memory>
#include <vector>
#include <map>
#include "InputManager.h"
#include "ControllerInput.h"


class dae::ControllerInput::ControllerInputImpl
{
public:
	ControllerInputImpl()
		:m_currState(new XINPUT_STATE[XUSER_MAX_COUNT]), m_prevState(new XINPUT_STATE[XUSER_MAX_COUNT])
	{
		ZeroMemory(m_currState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
		ZeroMemory(m_prevState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
	}

	~ControllerInputImpl()
	{
		delete[] m_currState;
		delete[] m_prevState;
		m_currState = nullptr;
		m_prevState = nullptr;
	}

	std::vector<std::pair<controlInput, std::shared_ptr<Command>>> ProcessInput()
	{
		std::swap(m_prevState, m_currState);

		for (DWORD i{}; i < XUSER_MAX_COUNT; ++i)
		{
			
			XInputGetState(i, &m_currState[i]);
		}

		std::vector<std::pair<controlInput, std::shared_ptr<Command>>> command{};

		for (auto& b : m_controllerCommands)
		{
			controlInput input{};
			
			if (IsDown(b.first))
			{
				input.isPressed = true;
				input.id = b.first.first;
				command.push_back(std::make_pair(input, (b.second)));
			}
			
			if (IsUp(b.first))
			{
				input.isPressed = false;
				input.id = b.first.first;
				command.push_back(std::make_pair(input, (b.second)));
			}
		}
		
		return command;
	}

	bool IsPressed(const std::pair<unsigned, controlButton>& controllerButton) const
	{
		return m_currState[controllerButton.first].Gamepad.wButtons & static_cast<unsigned int>(controllerButton.second);
	}

	bool IsDown(const std::pair<unsigned, controlButton>& controllerButton) const
	{
		auto buttonChanges = m_currState[controllerButton.first].Gamepad.wButtons ^ m_prevState[controllerButton.first].Gamepad.wButtons;
		int down = buttonChanges & m_currState[controllerButton.first].Gamepad.wButtons;
		return down & static_cast<unsigned int>(controllerButton.second);
	}

	bool IsUp(const std::pair<unsigned, controlButton>& controllerButton) const
	{
		auto buttonChanges = m_currState[controllerButton.first].Gamepad.wButtons ^ m_prevState[controllerButton.first].Gamepad.wButtons;
		int up = buttonChanges & ~(m_currState[controllerButton.first].Gamepad.wButtons);
		return up & static_cast<unsigned int>(controllerButton.second);
	}

	
	void AddCommand(std::map<controlButton, std::shared_ptr<Command>>& inputCommands, unsigned int id)
	{
		for (auto& c : inputCommands)
		{
			m_controllerCommands[std::make_pair(id, c.first)] = std::move(c.second);
		}
	}

private:
	using ControllerKey = std::pair<unsigned, controlButton>;
	using ControllerCommandsMap = std::map<ControllerKey, std::shared_ptr<Command>>;

	ControllerCommandsMap m_controllerCommands{};

	XINPUT_STATE* m_currState{};
	XINPUT_STATE* m_prevState{};
};

dae::ControllerInput::ControllerInput()
{
	m_pImpl = new ControllerInputImpl();
}

dae::ControllerInput::~ControllerInput()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

std::vector<std::pair<dae::controlInput, std::shared_ptr<Command>>> dae::ControllerInput::ProcessInput() const
{
	return m_pImpl->ProcessInput();
}

bool dae::ControllerInput::IsPressed(std::pair<unsigned, controlButton>& button) const
{
	return m_pImpl->IsPressed(button);
}

bool dae::ControllerInput::IsDown(std::pair<unsigned, controlButton>& button) const
{
	return m_pImpl->IsDown(button);
}

bool dae::ControllerInput::IsUp(std::pair<unsigned, controlButton>& button) const
{
	return m_pImpl->IsUp(button);
}

void dae::ControllerInput::AddCommand(std::map<controlButton, std::shared_ptr<Command>>& commands, unsigned int id)
{
	m_pImpl->AddCommand(commands, id);
}
