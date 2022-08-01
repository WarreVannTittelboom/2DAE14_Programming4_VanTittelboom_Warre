#include "PlayerTank.h"
#include <CollisionComp.h>
#include <Scene.h>
#include <map>
#include <InputManager.h>
#include "TronGame.h"
#include <TextureComp.h>
#include "PlayerCommands.h"
#include <Timer.h>
#include "PlayerBullet.h"
#include <math.h>  // for sin and cos
#include <GameObject.h>
#include <Scene.h>
#include <SceneManager.h>
#include<SceneObject.h>
#include "Teleporter.h"

#define PI 3.14159265

dae::PlayerTank::PlayerTank(dae::GameObject* gameObject,Scene& scene)
	: BaseComp(gameObject)
	, m_Scene(scene)
{

}

dae::PlayerTank::~PlayerTank()
{
}

void dae::PlayerTank::Initialize()
{
	//init controls
	auto playercol = std::make_shared<dae::CollisionComp>(m_pGameObject, 32.f, 32.f, true);
	m_pGameObject->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	m_playerHorizontalSprite = std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/PlayerTankHorizontal.png", 32, 32, false);
	m_pGameObject->AddComponent(m_playerHorizontalSprite);
	m_playerVerticalSprite = std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/PlayerTankVertical.png", 32, 32, true);
	m_pGameObject->AddComponent(m_playerVerticalSprite);

	InitTurretSprites();

	

	std::map<SDL_Scancode, std::shared_ptr<Command>> kInputMap{};
	std::map<controlButton, std::shared_ptr<Command>> cInputMap{};

	kInputMap[SDL_SCANCODE_LEFT] = std::make_shared<MoveLeft>(m_pGameObject);
	cInputMap[controlButton::DpadLeft] = std::make_shared<MoveLeft>(m_pGameObject);

	kInputMap[SDL_SCANCODE_RIGHT] = std::make_shared<MoveRight>(m_pGameObject);
	cInputMap[controlButton::DpadRight] = std::make_shared<MoveRight>(m_pGameObject);

	kInputMap[SDL_SCANCODE_UP] = std::make_shared<MoveUp>(m_pGameObject);
	cInputMap[controlButton::DpadUp] = std::make_shared<MoveUp>(m_pGameObject);

	kInputMap[SDL_SCANCODE_DOWN] = std::make_shared<MoveDown>(m_pGameObject);
	cInputMap[controlButton::DpadDown] = std::make_shared<MoveDown>(m_pGameObject);

	kInputMap[SDL_SCANCODE_LCTRL] = std::make_shared<DoShoot>(m_pGameObject);
	cInputMap[controlButton::ButtonA] = std::make_shared<DoShoot>(m_pGameObject);

	kInputMap[SDL_SCANCODE_Z] = std::make_shared<CannonLeft>(m_pGameObject);
	cInputMap[controlButton::LeftShoulder] = std::make_shared<CannonLeft>(m_pGameObject);

	kInputMap[SDL_SCANCODE_X] = std::make_shared<CannonRight>(m_pGameObject);
	cInputMap[controlButton::RightShoulder] = std::make_shared<CannonRight>(m_pGameObject);

	dae::InputManager::GetInstance().AddCommand(kInputMap, 0);
	dae::InputManager::GetInstance().AddCommand(cInputMap, 0);
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
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x - (deltaTime * m_PlayerSpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
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
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x + (deltaTime * m_PlayerSpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
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
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y + (deltaTime * m_PlayerSpeed), m_pGameObject->GetPosition().z);
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
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y - (deltaTime * m_PlayerSpeed), m_pGameObject->GetPosition().z);
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
			m_ShootCannonCooldown = 0.0f;
			auto bulletGo = std::make_shared<dae::GameObject>();
			float cosX = float(cos((m_TurretMoveIter * 10.f) * (PI / 180.0f)));
			float sinY = float(sin((m_TurretMoveIter * 10.f) * (PI / 180.0f)));
			auto bulletComp = std::make_shared<dae::PlayerBullet>(bulletGo.get(), m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y, cosX, sinY,m_Scene);
			bulletGo->AddComponent(bulletComp);
			auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
			scene.Add(bulletGo);
			//Test();
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
	//check if facing the right way if not flip the sprite accordingly
	//check if cannon is rotated the right if not rotate it accordingly
}

void dae::PlayerTank::OnColl(const GameObject* other)
{
	//std::cout << "testyes\n";
	//check if colliding with wall or enemy tank
	//if colliding with wall, move back
	//if colliding with enemy tank, damage enemy tank
	// If one rectangle is on left side of the other
		/*if (((other->GetComponent<dae::CollisionComp>()->m_Pos.x + other->GetComponent<dae::CollisionComp>()->m_Width - 2) > m_pGameObject->GetWorldPosition().x) && ((m_pGameObject->GetWorldPosition().x + m_pGameObject->GetComponent<dae::CollisionComp>()->m_Width) > other->GetComponent<dae::CollisionComp>()->m_Pos.x))

		{
			m_BlockMoveRight = true;
		}
		else if (((other->GetComponent<dae::CollisionComp>()->m_Pos.x + other->GetComponent<dae::CollisionComp>()->m_Width) > m_pGameObject->GetWorldPosition().x) && ((m_pGameObject->GetWorldPosition().x + m_pGameObject->GetComponent<dae::CollisionComp>()->m_Width) > other->GetComponent<dae::CollisionComp>()->m_Pos.x + 2))
		{
			m_BlockMoveLeft = true;
		}

	else if ((m_pGameObject->GetComponent<dae::CollisionComp>()->m_Pos.y + 2< (other->GetComponent<dae::CollisionComp>()->m_Pos.y + m_pGameObject->GetComponent<dae::CollisionComp>()->m_Height)) && other->GetComponent<dae::CollisionComp>()->m_Pos.y  < (m_pGameObject->GetComponent<dae::CollisionComp>()->m_Pos.y + other->GetComponent<dae::CollisionComp>()->m_Height))
	{	
		m_BlockMoveUp = true;
	}
	else if ((m_pGameObject->GetComponent<dae::CollisionComp>()->m_Pos.y  < (other->GetComponent<dae::CollisionComp>()->m_Pos.y + m_pGameObject->GetComponent<dae::CollisionComp>()->m_Height)) && other->GetComponent<dae::CollisionComp>()->m_Pos.y < (m_pGameObject->GetComponent<dae::CollisionComp>()->m_Pos.y + other->GetComponent<dae::CollisionComp>()->m_Height -2))
	{
		m_BlockMoveDown = true;
	}
	*/

	if (other->GetComponent<dae::Teleporter>())
	{
		m_pGameObject->SetPosition(300, -50);
	}
	else 
	{ 
	if(!((other->GetComponent<dae::CollisionComp>()->m_Pos.x + other->GetComponent<dae::CollisionComp>()->m_Width -2) > m_pGameObject->GetWorldPosition().x))

	{
		m_BlockMoveLeft = true;
	}
	if (!(((m_pGameObject->GetWorldPosition().x + m_pGameObject->GetComponent<dae::CollisionComp>()->m_Width) > other->GetComponent<dae::CollisionComp>()->m_Pos.x + 2)))
	{
		m_BlockMoveRight = true;
	}

	if (!(m_pGameObject->GetComponent<dae::CollisionComp>()->m_Pos.y + 2 < (other->GetComponent<dae::CollisionComp>()->m_Pos.y + m_pGameObject->GetComponent<dae::CollisionComp>()->m_Height)))
	{
		m_BlockMoveDown = true;
	}
	if (!(other->GetComponent<dae::CollisionComp>()->m_Pos.y < (m_pGameObject->GetComponent<dae::CollisionComp>()->m_Pos.y + other->GetComponent<dae::CollisionComp>()->m_Height - 2)))
	{
		m_BlockMoveUp = true;
	}
	}

}


void dae::PlayerTank::InitTurretSprites()
{
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon1.png", 32, 32, true));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon2.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon3.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon4.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon5.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon6.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon7.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon8.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon9.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon10.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon9.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon8.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon7.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon6.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon5.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon4.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon3.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon2.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon1.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = 8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon2.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon3.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon4.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon5.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon6.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon7.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon8.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon9.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon10.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = -8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipHorizontal = true;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon9.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon8.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon7.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon6.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon5.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon4.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon3.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
	m_playerCannonSprites.push_back(std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Cannon2.png", 32, 32, false));
	m_playerCannonSprites.back().get()->m_OffSetX = 8;
	m_playerCannonSprites.back().get()->m_OffSetY = -8;
	m_playerCannonSprites.back().get()->m_FlipVertical = true;
	m_pGameObject->AddComponent(m_playerCannonSprites.back());
}

void dae::PlayerTank::Test()
{
	auto bulletGo = std::make_shared<dae::GameObject>();
	float cosX = float(cos((m_TurretMoveIter * 10.f) * (PI / 180.0f)));
	float sinY = float(sin((m_TurretMoveIter * 10.f) * (PI / 180.0f)));
	auto bulletComp = std::make_shared<dae::PlayerBullet>(bulletGo.get(), m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y, cosX, sinY,m_Scene);
	bulletGo->AddComponent(bulletComp);
	auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
	scene.Add(bulletGo);
}
