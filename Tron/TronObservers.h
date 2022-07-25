#pragma once
#include <Observer.h>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "PlayerTank.h"

namespace dae
{
class CollisionObserver : public Observer
{
public:
	explicit CollisionObserver(std::shared_ptr<GameObject> playerTank)
	{
		m_pPlayerTank = playerTank;
	}
	~CollisionObserver() override = default;
	void OnNotify(const dae::GameObject* entity, Event event) override
	{
		switch (event)
		{
		case dae::Event::CollEvent:
		{
			//check if colling with enemy or bullet
			//if (auto pEnemy = entity->GetComponent<dae::test>())
			m_pPlayerTank->GetComponent<dae::PlayerTank>()->OnColl(entity);
		}
		break;
		}
	}
private:
	std::shared_ptr<GameObject>  m_pPlayerTank{};
};
}
