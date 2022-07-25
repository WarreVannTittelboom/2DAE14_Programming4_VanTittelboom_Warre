#include "PlayerTank.h"
#include <CollisionComp.h>
#include <Scene.h>
#include <map>
#include <InputManager.h>
#include "TronGame.h"
#include <TextureComp.h>
#include "PlayerCommands.h"
#include <Timer.h>

dae::PlayerTank::PlayerTank(dae::GameObject* gameObject)
	: BaseComp(gameObject)
	, m_Scene(dae::SceneManager::GetInstance().GetScene("Menu"))
{

}

dae::PlayerTank::~PlayerTank()
{
}

void dae::PlayerTank::Initialize()
{
	//init controls

	CollisionObserver* collideObserver = new CollisionObserver();
	auto playercol = std::make_shared<dae::CollisionComp>(m_pGameObject, 32.f, 32.f, true);
	m_pGameObject->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	m_pGameObject->GetComponent<CollisionComp>()->GetSubject()->AddObserver(collideObserver);
	m_pGameObject->SetPosition(224, -320);
	m_playerHorizontalSprite = std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/PlayerTankHorizontal.png", 32, 32, false);
	m_pGameObject->AddComponent(m_playerHorizontalSprite);
	m_playerVerticalSprite = std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/PlayerTankVertical.png", 32, 32, true);
	m_pGameObject->AddComponent(m_playerVerticalSprite);

	InitTurretSprites();

	

	std::map<SDL_Scancode, std::shared_ptr<Command>> kInputMap{};
	std::map<controlButton, std::shared_ptr<Command>> cInputMap{};

	kInputMap[SDL_SCANCODE_A] = std::make_shared<MoveLeft>(m_pGameObject);
	cInputMap[controlButton::DpadLeft] = std::make_shared<MoveLeft>(m_pGameObject);

	kInputMap[SDL_SCANCODE_D] = std::make_shared<MoveRight>(m_pGameObject);
	cInputMap[controlButton::DpadRight] = std::make_shared<MoveRight>(m_pGameObject);

	kInputMap[SDL_SCANCODE_W] = std::make_shared<MoveUp>(m_pGameObject);
	cInputMap[controlButton::DpadUp] = std::make_shared<MoveUp>(m_pGameObject);

	kInputMap[SDL_SCANCODE_S] = std::make_shared<MoveDown>(m_pGameObject);
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
		m_pGameObject->SetPosition(m_pGameObject->GetPosition().x - (deltaTime * m_PlayerSpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
		m_playerHorizontalSprite.get()->m_IsActive = true;
		m_playerVerticalSprite.get()->m_IsActive = false;
		m_playerHorizontalSprite.get()->m_FlipHorizontal = true;
		m_playerHorizontalSprite.get()->m_FlipVertical = false;
	}
	else if (m_MoveRight)
	{
		m_pGameObject->SetPosition(m_pGameObject->GetPosition().x + (deltaTime * m_PlayerSpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
		m_playerHorizontalSprite.get()->m_IsActive = true;
		m_playerVerticalSprite.get()->m_IsActive = false;
		m_playerHorizontalSprite.get()->m_FlipHorizontal = false;
		m_playerHorizontalSprite.get()->m_FlipVertical = false;
	}
	else if (m_MoveUp)
	{
		m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y + (deltaTime * m_PlayerSpeed), m_pGameObject->GetPosition().z);
		m_playerHorizontalSprite.get()->m_IsActive = false;
		m_playerVerticalSprite.get()->m_IsActive = true;
		m_playerVerticalSprite.get()->m_FlipHorizontal = false;
		m_playerVerticalSprite.get()->m_FlipVertical = false;
	}
	else if (m_MoveDown)
	{
		m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y - (deltaTime * m_PlayerSpeed), m_pGameObject->GetPosition().z);
		m_playerHorizontalSprite.get()->m_IsActive = false;
		m_playerVerticalSprite.get()->m_IsActive = true;
		m_playerVerticalSprite.get()->m_FlipHorizontal = false;
		m_playerVerticalSprite.get()->m_FlipVertical = true;
	}

	if (m_DoShoot)
	{
		//check if not on cooldown and if not shoot bullet
	}


	//xor for checking if cannon should be turned
	if (m_MoveCannonLeft != m_MoveCannonRight)
	{
		if (m_MoveCannonCooldown >= 0.04f)
		{
			m_MoveCannonCooldown = 0.f;

			if (m_MoveCannonLeft)
			{
				++m_TurretMoveIter;
				if (m_TurretMoveIter >= m_playerCannonSprites.size())
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


}

void dae::PlayerTank::Render() const
{
	//check if facing the right way if not flip the sprite accordingly
	//check if cannon is rotated the right if not rotate it accordingly
}

void dae::PlayerTank::OnColl(GameObject* other)
{
	//check if collding with enemy or bullet if so kill and lose life
	//also call during update to check if colliding with wall?
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
