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

		virtual void OnNotify(const dae::GameObject& entity, Event event) = 0;
	};



	class CollisionObserver : public Observer
	{
	public:
		~CollisionObserver() override = default;
		void OnNotify(const dae::GameObject& /*entity*/, Event event) override
		{
			switch (event)
			{
			case dae::Event::CollEvent:
			{
				std::cout << "Colliding!\n";
			}
			break;
			}
		}
	};
}
