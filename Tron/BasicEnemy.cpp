#pragma once
#include "BasicEnemy.h"
#include "TronObservers.h"
#include "Timer.h"

#define PI 3.14159265

dae::BasicEnemy::BasicEnemy(GameObject* gameObject, float x, float y, float w, float h, std::shared_ptr<GameObject> playerTank, Scene& scene)
	:BaseComp(gameObject)
	,m_Scene(scene)
	,m_PosX(x)
	,m_PosY(y)
	,m_Width(w)
	,m_Height(h)
	,m_PlayerTank(playerTank)
{
}

dae::BasicEnemy::~BasicEnemy()
{
}

void dae::BasicEnemy::Initialize()
{
	m_pGameObject->SetPosition(m_PosX, -m_PosY);
	m_enemyHorizontalSprite = std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/EnemyTankHorizontal.png", (int)m_Width, (int)m_Height, false);
	m_pGameObject->AddComponent(m_enemyHorizontalSprite);
	m_enemyVerticalSprite = std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/EnemyTankVertical.png", (int)m_Width, (int)m_Height, true);
	m_pGameObject->AddComponent(m_enemyVerticalSprite);
	auto playercol = std::make_shared<dae::CollisionComp>(m_pGameObject, m_Width, m_Height, true);
	m_pGameObject->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	m_pGameObject->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new EnemyCollisionObserver(m_PlayerTank));
}


void dae::BasicEnemy::Update()
{
	float playerPosX = m_PlayerTank->GetPosition().x;
	float playerPosY = m_PlayerTank->GetPosition().y;

	float valueDiffX{0.f};
	float valueDiffY{0.f};
	float diffX = playerPosX - m_pGameObject->GetPosition().x;
	if (diffX < 0) { valueDiffX = diffX * -1;}
	else { valueDiffX = diffX; }
	float diffY = playerPosY - m_pGameObject->GetPosition().y;
	if (diffY < 0) { valueDiffY = diffY * -1; }
	else { valueDiffY = diffY; }
	float deltaTime = Timer::GetInstance().GetDeltaTime();
	m_ShootCannonCooldown += deltaTime;
	if (valueDiffX > valueDiffY && diffX < 0 && (!m_BlockMoveLeft))
	{
		
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
			ShootCannon(180.f);
	}
	else if (valueDiffX > valueDiffY && diffX > 0 && (!m_BlockMoveRight))
	{
		
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
			ShootCannon(0.f);
		
	}
	else if (valueDiffX < valueDiffY && diffY > 0 && (!m_BlockMoveUp))
	{
		
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = false;
			ShootCannon(90.f);
		
	}
	else if (valueDiffX < valueDiffY && diffY < 0 && (!m_BlockMoveDown))
	{
		
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
			ShootCannon(270.f);
		
	}
	else
	{
		if (m_BlockMoveLeft && (!m_BlockMoveUp))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = false;
			ShootCannon(90.f);
			
		}
		else if (m_BlockMoveLeft && m_BlockMoveUp && (!m_BlockMoveDown))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
			ShootCannon(270.f);
		}
		else if (m_BlockMoveLeft && (!m_BlockMoveRight))
		{

			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
			ShootCannon(0.f);
		}
		else if (m_BlockMoveRight && (!m_BlockMoveUp))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = false;
			ShootCannon(90.f);
		}
		else if (m_BlockMoveRight && m_BlockMoveUp && (!m_BlockMoveDown))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
			ShootCannon(270.f);
		}
		else if (m_BlockMoveRight && (!m_BlockMoveLeft))
		{

			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
			ShootCannon(180.f);
		}
		
		else if (m_BlockMoveUp && (!m_BlockMoveLeft))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
			ShootCannon(180.f);
		}
		else if (m_BlockMoveUp && m_BlockMoveLeft && (!m_BlockMoveRight))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
			ShootCannon(0.f);
		}
		else if (m_BlockMoveUp && (!m_BlockMoveDown))
		{

			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
			ShootCannon(270.f);
		}

		else if (m_BlockMoveDown && (!m_BlockMoveLeft))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
			ShootCannon(180.f);
		}
		else if (m_BlockMoveDown && m_BlockMoveLeft && (!m_BlockMoveRight))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
			ShootCannon(0.f);
		}
		else if (m_BlockMoveDown && (!m_BlockMoveUp))
		{

			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = false;
			ShootCannon(90.f);
		}

		
	}
	m_BlockMoveRight = false;
	m_BlockMoveLeft = false;
	m_BlockMoveUp = false;
	m_BlockMoveDown = false;
}

void dae::BasicEnemy::OnColl(const GameObject* other)
{
	if (!((other->GetComponent<dae::CollisionComp>()->m_Pos.x + other->GetComponent<dae::CollisionComp>()->m_Width - 2) > m_pGameObject->GetWorldPosition().x))

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

void dae::BasicEnemy::ShootCannon(float degreesAngle)
{
	if (m_ShootCannonCooldown >= 1.f)
	{
		m_ShootCannonCooldown = 0.0f;
		auto bulletGo = std::make_shared<dae::GameObject>();
		float cosX = float(cos((degreesAngle) * (PI / 180.0f)));
		float sinY = float(sin((degreesAngle) * (PI / 180.0f)));
		auto bulletComp = std::make_shared<dae::EnemyBullet>(bulletGo.get(), m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y, cosX, sinY, m_Scene);
		bulletGo->AddComponent(bulletComp);
		auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
		scene.Add(bulletGo);
	}
}

bool dae::BasicEnemy::DoDamage()
{
	--m_Health;
	if(m_Health <= 0)
	{
		dae::TronGame::GetInstance().m_Score += 100;
		m_Scene.Remove(m_pGameObject);
		return true;
		
	}
	return false;
}

