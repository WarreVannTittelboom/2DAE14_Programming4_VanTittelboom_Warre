#pragma once
#include <Observer.h>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "PlayerTank.h"
#include "PlayerBullet.h"
#include "Button.h"
#include "Teleporter.h"
#include "Wall.h"
#include "BasicEnemy.h"

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
	void OnNotify(const dae::GameObject* o, const dae::GameObject* e, Event event) override
	{
		switch (event)
		{
		case dae::Event::CollEvent:
		{
			//check if colling with enemy or bullet
			//if (auto pEnemy = entity->GetComponent<dae::test>())
			
			if (o->GetComponent<dae::BasicEnemy>())
			{
				o->GetComponent<dae::BasicEnemy>()->OnColl(e);
			}
			else if (o->GetComponent<dae::PlayerTank>())
			{
				o->GetComponent<dae::PlayerTank>()->OnColl(e);
			}
			
		}
		break;
		}
	}
private:
	std::shared_ptr<GameObject>  m_pPlayerTank{};
};

class PlayerBulletObserver : public Observer
{
public:
	explicit PlayerBulletObserver()
	{
	}
	~PlayerBulletObserver() override = default;
	void OnNotify(const dae::GameObject* o, const dae::GameObject* e,Event event) override
	{
		switch (event)
		{
		case dae::Event::CollEvent:
		{
			if (auto pPlayerBullet = e->GetComponent<dae::PlayerBullet>())
			{		
				pPlayerBullet->OnColl(o);
			} 
		}
		break;
		}
	}
};

class ButtonObserver : public Observer
{
public:
	explicit ButtonObserver()
	{
	}
	~ButtonObserver() override = default;
	void OnNotify(const dae::GameObject* o, const dae::GameObject* e, Event event) override
	{
		switch (event)
		{
		case dae::Event::CollEvent:
		{
			if (auto pPlayerBullet = e->GetComponent<dae::Button>())
			{
				pPlayerBullet->OnColl(o);
			}
		}
		break;
		}
	}
};
class TeleportCollisionObserver : public Observer
{
public:
	explicit TeleportCollisionObserver(std::shared_ptr<GameObject> playerTank)
	{
		m_pPlayerTank = playerTank;
	}
	~TeleportCollisionObserver() override = default;
	void OnNotify(const dae::GameObject* o, const dae::GameObject* e, Event event) override
	{
		switch (event)
		{
		case dae::Event::CollEvent:
		{
			//check if colling with enemy or bullet
			//if (auto pEnemy = entity->GetComponent<dae::test>())
			if (auto pPlayerBullet = o->GetComponent<dae::PlayerTank>())
			{
				o->GetComponent<dae::PlayerTank>()->OnColl(e);
			}
		}
		break;
		}
	}
private:
	std::shared_ptr<GameObject>  m_pPlayerTank{};
};

class EnemyCollisionObserver : public Observer
{
public:
	explicit EnemyCollisionObserver(std::shared_ptr<GameObject> playerTank)
	{
		m_pPlayerTank = playerTank;
	}
	~EnemyCollisionObserver() override = default;
	void OnNotify(const dae::GameObject* o, const dae::GameObject* e, Event event) override
	{
		switch (event)
		{
		case dae::Event::CollEvent:
		{
			//check if colling with enemy or bullet
			//if (auto pEnemy = entity->GetComponent<dae::test>())
			if (o->GetComponent<dae::PlayerTank>())
			{
				o->GetComponent<dae::PlayerTank>()->OnColl(e);
			}
			else if (o->GetComponent<dae::BasicEnemy>())
			{
				o->GetComponent<dae::BasicEnemy>()->OnColl(e);
			}
		}
		break;
		}
	}
private:
	std::shared_ptr<GameObject>  m_pPlayerTank{};
};

}
