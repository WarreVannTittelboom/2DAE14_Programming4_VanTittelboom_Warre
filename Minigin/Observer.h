#pragma once

namespace dae
{
	class GameObject;

	enum class Event
	{
		CollEvent,
		test2
	};

	class Observer
	{
	public:
		virtual ~Observer() {};
		
		virtual void OnNotify(const dae::GameObject* o, const dae::GameObject* e, Event event) = 0;
	};
}


	