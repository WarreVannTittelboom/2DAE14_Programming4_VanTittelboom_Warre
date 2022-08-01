#pragma once
#include "Observer.h"
#include <vector>
#include <memory>
#include <iostream>

namespace dae
{
	class GameObject;
	class Subject
	{
	public:
		Subject() = default;
		~Subject();
		void AddObserver(Observer* observer);
		void RemoveObserver(const Observer* observer);
		void Notify(const dae::GameObject* o, const dae::GameObject* e, Event event);
	private:
		std::vector<Observer*> m_pObservers{};
	};
}

