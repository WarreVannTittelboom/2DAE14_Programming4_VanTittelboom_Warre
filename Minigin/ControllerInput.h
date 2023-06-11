#pragma once
#include <memory>
#include <map>
#include <vector>
class Command;

namespace dae
{

	enum class controlButton
	{
		DpadUp = 0x0001,
		DpadDown = 0x0002,
		DpadLeft = 0x0004,
		DpadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LeftThumb = 0x0040,
		RightThumb = 0x0080,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
	};
	struct controlInput
	{
		unsigned int id;
		bool isPressed;
	};
	
	class ControllerInput
	{
	public:
		explicit ControllerInput();
		~ControllerInput();

		std::vector<std::pair<controlInput, std::shared_ptr<Command>>> ProcessInput() const;
		bool IsPressed(std::pair<unsigned, controlButton>& button) const;
		bool IsDown(std::pair<unsigned, controlButton>& button) const;
		bool IsUp(std::pair<unsigned, controlButton>& button) const;

		void AddCommand(std::map<controlButton, std::shared_ptr<Command>>& inputCommands, unsigned int id);
	private:
		class ControllerInputImpl;
		ControllerInputImpl* m_pImpl;
	};
}
