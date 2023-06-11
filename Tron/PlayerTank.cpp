#pragma once
#include "PlayerTank.h"
#include <CollisionComp.h>
#include <map>
#include <InputManager.h>
#include "TronGame.h"
#include "PlayerCommands.h"
#include <Timer.h>
#include "PlayerBullet.h"
#include <math.h>  // for sin and cos
#include <Scene.h>
#include <SceneManager.h>
#include<SceneObject.h>
#include "Teleporter.h"
#include "BasicEnemy.h"
#include "EnemyBullet.h"
#include "RecognizerEnemy.h"
#include <Font.h>
#include <TextComp.h>
#include "HighScoreMenu.h"
#include "ServiceLocator.h"

#define PI 3.14159265

dae::PlayerTank::PlayerTank(dae::GameObject* gameObject, Scene& scene, unsigned int id)
	: BaseComp(gameObject)
	, m_Scene(scene)
	, m_Id(id)
{

}

dae::PlayerTank::~PlayerTank()
{
}

void dae::PlayerTank::Initialize()
{
	//init controls
	auto playercol = std::make_shared<dae::CollisionComp>(GetGameObject(), 32.f, 32.f, true);
	GetGameObject()->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	if (m_Id == 0)
	{
		std::map<controlButton, std::shared_ptr<Command>> cInputMap{};

		cInputMap[controlButton::DpadLeft] = std::make_shared<MoveLeft>(GetGameObject());

		cInputMap[controlButton::DpadRight] = std::make_shared<MoveRight>(GetGameObject());

		cInputMap[controlButton::DpadUp] = std::make_shared<MoveUp>(GetGameObject());

		cInputMap[controlButton::DpadDown] = std::make_shared<MoveDown>(GetGameObject());

		cInputMap[controlButton::ButtonA] = std::make_shared<DoShoot>(GetGameObject());

		cInputMap[controlButton::LeftShoulder] = std::make_shared<CannonLeft>(GetGameObject());

		cInputMap[controlButton::RightShoulder] = std::make_shared<CannonRight>(GetGameObject());





		dae::InputManager::GetInstance().AddCommand(cInputMap, 0);

		std::map<SDL_Scancode, std::shared_ptr<Command>> kInputMap{};

		kInputMap[SDL_SCANCODE_LEFT] = std::make_shared<MoveLeft>(GetGameObject());

		kInputMap[SDL_SCANCODE_RIGHT] = std::make_shared<MoveRight>(GetGameObject());

		kInputMap[SDL_SCANCODE_UP] = std::make_shared<MoveUp>(GetGameObject());

		kInputMap[SDL_SCANCODE_DOWN] = std::make_shared<MoveDown>(GetGameObject());

		kInputMap[SDL_SCANCODE_LCTRL] = std::make_shared<DoShoot>(GetGameObject());

		kInputMap[SDL_SCANCODE_Z] = std::make_shared<CannonLeft>(GetGameObject());

		kInputMap[SDL_SCANCODE_X] = std::make_shared<CannonRight>(GetGameObject());





		dae::InputManager::GetInstance().AddCommand(kInputMap, m_Id);



		m_playerHorizontalSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/PlayerTankHorizontal.png", 32, 32, false);
		GetGameObject()->AddComponent(m_playerHorizontalSprite);
		m_playerVerticalSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/PlayerTankVertical.png", 32, 32, true);
		GetGameObject()->AddComponent(m_playerVerticalSprite);
	}
	if (m_Id == 1)
	{

		std::map<SDL_Scancode, std::shared_ptr<Command>> kInputMap{};

		kInputMap[SDL_SCANCODE_LEFT] = std::make_shared<MoveLeft>(GetGameObject());

		kInputMap[SDL_SCANCODE_RIGHT] = std::make_shared<MoveRight>(GetGameObject());

		kInputMap[SDL_SCANCODE_UP] = std::make_shared<MoveUp>(GetGameObject());

		kInputMap[SDL_SCANCODE_DOWN] = std::make_shared<MoveDown>(GetGameObject());

		kInputMap[SDL_SCANCODE_LCTRL] = std::make_shared<DoShoot>(GetGameObject());

		kInputMap[SDL_SCANCODE_Z] = std::make_shared<CannonLeft>(GetGameObject());

		kInputMap[SDL_SCANCODE_X] = std::make_shared<CannonRight>(GetGameObject());






		dae::InputManager::GetInstance().AddCommand(kInputMap, m_Id);

		std::map<controlButton, std::shared_ptr<Command>> cInputMap{};

		cInputMap[controlButton::DpadLeft] = std::make_shared<MoveLeft>(GetGameObject());

		cInputMap[controlButton::DpadRight] = std::make_shared<MoveRight>(GetGameObject());

		cInputMap[controlButton::DpadUp] = std::make_shared<MoveUp>(GetGameObject());

		cInputMap[controlButton::DpadDown] = std::make_shared<MoveDown>(GetGameObject());

		cInputMap[controlButton::ButtonA] = std::make_shared<DoShoot>(GetGameObject());

		cInputMap[controlButton::LeftShoulder] = std::make_shared<CannonLeft>(GetGameObject());

		cInputMap[controlButton::RightShoulder] = std::make_shared<CannonRight>(GetGameObject());





		dae::InputManager::GetInstance().AddCommand(cInputMap, 1);



		m_playerHorizontalSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/PlayerTankHorizontal.png", 32, 32, false);
		GetGameObject()->AddComponent(m_playerHorizontalSprite);
		m_playerVerticalSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/PlayerTankVertical.png", 32, 32, true);
		GetGameObject()->AddComponent(m_playerVerticalSprite);
	}
	if (m_Id == 2)
	{
		std::map<controlButton, std::shared_ptr<Command>> cInputMap{};

		cInputMap[controlButton::DpadLeft] = std::make_shared<MoveLeft>(GetGameObject());

		cInputMap[controlButton::DpadRight] = std::make_shared<MoveRight>(GetGameObject());

		cInputMap[controlButton::DpadUp] = std::make_shared<MoveUp>(GetGameObject());

		cInputMap[controlButton::DpadDown] = std::make_shared<MoveDown>(GetGameObject());

		cInputMap[controlButton::ButtonA] = std::make_shared<DoShoot>(GetGameObject());

		cInputMap[controlButton::LeftShoulder] = std::make_shared<CannonLeft>(GetGameObject());

		cInputMap[controlButton::RightShoulder] = std::make_shared<CannonRight>(GetGameObject());





		dae::InputManager::GetInstance().AddCommand(cInputMap, 0);



		m_playerHorizontalSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Player2TankHorizontal.png", 32, 32, false);
		GetGameObject()->AddComponent(m_playerHorizontalSprite);
		m_playerVerticalSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Player2TankVertical.png", 32, 32, true);
		GetGameObject()->AddComponent(m_playerVerticalSprite);
	}


	InitTurretSprites();
}

void dae::PlayerTank::Update()
{
	//check for movement input of cannon and tank, rotate sprites accordingly
	//check for input for shooting
	//no moveent if colliding in that direction
	float deltaTime = Timer::GetInstance().GetDeltaTime();
	if (m_MoveLeft)
	{
		if (!m_BlockMoveLeft)
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x - (deltaTime * m_PlayerSpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
			m_playerHorizontalSprite.get()->m_IsActive = true;
			m_playerVerticalSprite.get()->m_IsActive = false;
			m_playerHorizontalSprite.get()->m_FlipHorizontal = true;
			m_playerHorizontalSprite.get()->m_FlipVertical = false;
		}
	}
	else if (m_MoveRight)
	{
		if (!m_BlockMoveRight)
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x + (deltaTime * m_PlayerSpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
			m_playerHorizontalSprite.get()->m_IsActive = true;
			m_playerVerticalSprite.get()->m_IsActive = false;
			m_playerHorizontalSprite.get()->m_FlipHorizontal = false;
			m_playerHorizontalSprite.get()->m_FlipVertical = false;
		}
	}
	else if (m_MoveUp)
	{
		if (!m_BlockMoveUp)
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y + (deltaTime * m_PlayerSpeed), GetGameObject()->GetPosition().z);
			m_playerHorizontalSprite.get()->m_IsActive = false;
			m_playerVerticalSprite.get()->m_IsActive = true;
			m_playerVerticalSprite.get()->m_FlipHorizontal = false;
			m_playerVerticalSprite.get()->m_FlipVertical = false;
		}
	}
	else if (m_MoveDown)
	{
		if (!m_BlockMoveDown)
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y - (deltaTime * m_PlayerSpeed), GetGameObject()->GetPosition().z);
			m_playerHorizontalSprite.get()->m_IsActive = false;
			m_playerVerticalSprite.get()->m_IsActive = true;
			m_playerVerticalSprite.get()->m_FlipHorizontal = false;
			m_playerVerticalSprite.get()->m_FlipVertical = true;
		}
	}

	if (m_DoShoot)
	{
		if (m_ShootCannonCooldown >= 0.5f)
		{
			ServiceLocator::GetInstance().GetSoundSystem().Enqueue("../Data/shoot.wav", 0, 4);
			m_ShootCannonCooldown = 0.0f;
			auto bulletGo = std::make_shared<dae::GameObject>();
			float cosX = float(cos((m_TurretMoveIter * 10.f) * (PI / 180.0f)));
			float sinY = float(sin((m_TurretMoveIter * 10.f) * (PI / 180.0f)));
			auto bulletComp = std::make_shared<dae::PlayerBullet>(bulletGo.get(), GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y, cosX, sinY, m_Scene, m_Id);
			bulletGo->AddComponent(bulletComp);
			auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
			scene.Add(bulletGo);
		}
		//check if not on cooldown and if not shoot bullet
	}
	m_ShootCannonCooldown += deltaTime;


	//xor for checking if cannon should be turned
	if (m_MoveCannonLeft != m_MoveCannonRight)
	{
		if (m_MoveCannonCooldown >= 0.04f)
		{
			m_MoveCannonCooldown = 0.f;

			if (m_MoveCannonLeft)
			{
				++m_TurretMoveIter;
				if ((size_t)m_TurretMoveIter >= m_playerCannonSprites.size())
				{
					m_TurretMoveIter -= unsigned int(m_playerCannonSprites.size());
				}
				for (auto sprite : m_playerCannonSprites)
				{
					sprite.get()->m_IsActive = false;
				}
				m_playerCannonSprites.at(m_TurretMoveIter).get()->m_IsActive = true;
			}
			else
			{
				--m_TurretMoveIter;
				if (m_TurretMoveIter < 0)
				{
					m_TurretMoveIter += int(m_playerCannonSprites.size());
				}
				for (auto sprite : m_playerCannonSprites)
				{
					sprite.get()->m_IsActive = false;
				}
				m_playerCannonSprites.at(m_TurretMoveIter).get()->m_IsActive = true;
			}
		}
		m_MoveCannonCooldown += deltaTime;
	}

	m_BlockMoveRight = false;
	m_BlockMoveLeft = false;
	m_BlockMoveUp = false;
	m_BlockMoveDown = false;
}

void dae::PlayerTank::Render() const
{
}

void dae::PlayerTank::OnColl(const GameObject* other)
{

	if (other->GetComponent<dae::Teleporter>())
	{
		int randomx = 20 + (std::rand() % (440 - 20 + 1));
		int randomy = 20 + (std::rand() % (482 - 20 + 1));
		GetGameObject()->SetPosition(randomx, -randomy);
	}
	else if (other->GetComponent<dae::BasicEnemy>()|| other->GetComponent<dae::RecognizerEnemy>() || other->GetComponent<dae::EnemyBullet>())
	{
		if (m_Id == 2)
		{
			dae::TronGame::GetInstance().m_LivesP2 -= 1;
			dae::TronGame::GetInstance().m_DeadP2 = true;
		}
		else
		{
			dae::TronGame::GetInstance().m_LivesP1 -= 1;
			dae::TronGame::GetInstance().m_DeadP1 = true;
		}
		GetGameObject()->SetPosition(-800, 800);
		//GetGameObject()->MarkDestroy();
		if (dae::TronGame::GetInstance().m_DeadP1 && dae::TronGame::GetInstance().m_DeadP2 || (dae::TronGame::GetInstance().m_DeadP1 && (m_Scene.m_FileName == "SingleLevel1" || m_Scene.m_FileName == "SingleLevel2" || m_Scene.m_FileName == "SingleLevel3")))
		{
			m_Scene.m_DeadEnemyCount = 0;
			dae::TronGame::GetInstance().m_DeadP2 = false;
			dae::TronGame::GetInstance().m_DeadP1 = false;
			dae::TronGame::GetInstance().ResetLevelForNext();
		}
		

		if (dae::TronGame::GetInstance().m_LivesP1 < 0 && 0 > dae::TronGame::GetInstance().m_LivesP2 ||(( m_Scene.m_FileName == "SingleLevel1" || m_Scene.m_FileName == "SingleLevel2" || m_Scene.m_FileName == "SingleLevel3") && dae::TronGame::GetInstance().m_LivesP1 < 0))
		{
			dae::TronGame::GetInstance().m_LivesP2 = 3;
			dae::TronGame::GetInstance().m_LivesP1 = 3;
			auto value = dae::TronGame::GetInstance().m_Score;
			dae::SceneManager::GetInstance().SetScene("gameoverscene");
			dae::SceneManager::GetInstance().GetActiveScene().FindObjectOfType<dae::TextComp>()->SetText("Score: " + std::to_string((value)));
			dae::SceneManager::GetInstance().GetActiveScene().FindObjectOfType<dae::HighScoreMenu>()->LoadScores();
		}
	}
	else
	{
		if (!((other->GetComponent<dae::CollisionComp>()->m_Pos.x + other->GetComponent<dae::CollisionComp>()->m_Width - 2) > GetGameObject()->GetWorldPosition().x))

		{
			m_BlockMoveLeft = true;
		}
		if (!(((GetGameObject()->GetWorldPosition().x + GetGameObject()->GetComponent<dae::CollisionComp>()->m_Width) > other->GetComponent<dae::CollisionComp>()->m_Pos.x + 2)))
		{
			m_BlockMoveRight = true;
		}

		if (!(GetGameObject()->GetComponent<dae::CollisionComp>()->m_Pos.y + 2 < (other->GetComponent<dae::CollisionComp>()->m_Pos.y + GetGameObject()->GetComponent<dae::CollisionComp>()->m_Height)))
		{
			m_BlockMoveDown = true;
		}
		if (!(other->GetComponent<dae::CollisionComp>()->m_Pos.y < (GetGameObject()->GetComponent<dae::CollisionComp>()->m_Pos.y + other->GetComponent<dae::CollisionComp>()->m_Height - 2)))
		{
			m_BlockMoveUp = true;
		}
	}

}


void dae::PlayerTank::InitTurretSprites()
{
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon1.png", 32, 32, true));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon2.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon3.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon4.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon5.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon6.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon7.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon8.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon9.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon10.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon9.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon8.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon7.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon6.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon5.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon4.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon3.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon2.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon1.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon2.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon3.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon4.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon5.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon6.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon7.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon8.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon9.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon10.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon9.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon8.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon7.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon6.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon5.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon4.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon3.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Cannon2.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	GetGameObject()->AddComponent(m_playerCannonSprites.back());
}