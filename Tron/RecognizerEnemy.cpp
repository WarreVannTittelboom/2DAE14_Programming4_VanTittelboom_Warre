#pragma once
#include "RecognizerEnemy.h"
#include "TronObservers.h"
#include "Timer.h"
#include "PlayerTank.h"


dae::RecognizerEnemy::RecognizerEnemy(GameObject* gameObject, float x, float y, float w, float h, std::shared_ptr<GameObject> playerTank, Scene& scene)
	:BaseComp(gameObject)
	, m_Scene(scene)
	, m_PosX(x)
	, m_PosY(y)
	, m_Width(w)
	, m_Height(h)
	, m_PlayerTank(playerTank)
{
}

dae::RecognizerEnemy::~RecognizerEnemy()
{
}

void dae::RecognizerEnemy::Initialize()
{
	m_pGameObject->SetPosition(m_PosX, -m_PosY);
	m_enemyHorizontalSprite = std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/rEnemyTankHorizontal.png", (int)m_Width, (int)m_Height, false);
	m_pGameObject->AddComponent(m_enemyHorizontalSprite);
	m_enemyVerticalSprite = std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/rEnemyTankVertical.png", (int)m_Width, (int)m_Height, true);
	m_pGameObject->AddComponent(m_enemyVerticalSprite);
	auto playercol = std::make_shared<dae::CollisionComp>(m_pGameObject, m_Width, m_Height, true);
	m_pGameObject->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	m_pGameObject->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new EnemyCollisionObserver(m_PlayerTank));
}


void dae::RecognizerEnemy::Update()
{
	float playerPosX = m_PlayerTank->GetPosition().x;
	float playerPosY = m_PlayerTank->GetPosition().y;

	float valueDiffX{ 0.f };
	float valueDiffY{ 0.f };
	float diffX = playerPosX - m_pGameObject->GetPosition().x;
	if (diffX < 0) { valueDiffX = diffX * -1; }
	else{ valueDiffX = diffX;  }
	float diffY = playerPosY - m_pGameObject->GetPosition().y;
	if (diffY < 0) { valueDiffY = diffY * -1; }
	else { valueDiffY = diffY; }
	float deltaTime = Timer::GetInstance().GetDeltaTime();
	if (valueDiffX > valueDiffY && diffX < 0 && (!m_BlockMoveLeft))
	{

		m_pGameObject->SetPosition(m_pGameObject->GetPosition().x - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
		m_enemyHorizontalSprite.get()->m_IsActive = true;
		m_enemyVerticalSprite.get()->m_IsActive = false;
		m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
		m_enemyHorizontalSprite.get()->m_FlipVertical = false;
	}
	else if (valueDiffX > valueDiffY && diffX > 0 && (!m_BlockMoveRight))
	{

		m_pGameObject->SetPosition(m_pGameObject->GetPosition().x + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
		m_enemyHorizontalSprite.get()->m_IsActive = true;
		m_enemyVerticalSprite.get()->m_IsActive = false;
		m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
		m_enemyHorizontalSprite.get()->m_FlipVertical = false;

	}
	else if (valueDiffX < valueDiffY && diffY > 0 && (!m_BlockMoveUp))
	{

		m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
		m_enemyHorizontalSprite.get()->m_IsActive = false;
		m_enemyVerticalSprite.get()->m_IsActive = true;
		m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
		m_enemyVerticalSprite.get()->m_FlipVertical = false;

	}
	else if (valueDiffX < valueDiffY && diffY < 0 && (!m_BlockMoveDown))
	{

		m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
		m_enemyHorizontalSprite.get()->m_IsActive = false;
		m_enemyVerticalSprite.get()->m_IsActive = true;
		m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
		m_enemyVerticalSprite.get()->m_FlipVertical = true;

	}
	else
	{
		if (m_BlockMoveLeft && diffY > 0 && (!m_BlockMoveUp))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = false;

		}
		else if (m_BlockMoveLeft && diffY < 0 && (!m_BlockMoveDown))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
		}
		else if (m_BlockMoveLeft && (!m_BlockMoveRight))
		{

			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveRight && diffY > 0 && (!m_BlockMoveUp))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveRight && diffY < 0 && (!m_BlockMoveDown))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
		}
		else if (m_BlockMoveRight && (!m_BlockMoveLeft))
		{

			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}

		else if (m_BlockMoveUp && diffX < 0 && (!m_BlockMoveLeft))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveUp && diffX > 0 && (!m_BlockMoveRight))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveUp && (!m_BlockMoveDown))
		{

			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
		}

		else if (m_BlockMoveDown && diffX < 0 && (!m_BlockMoveLeft))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x - (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveDown && diffX > 0 && (!m_BlockMoveRight))
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().y, m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveDown && (!m_BlockMoveUp))
		{

			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, m_pGameObject->GetPosition().y + (deltaTime * m_EnemySpeed), m_pGameObject->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = false;
		}


	}
	m_BlockMoveRight = false;
	m_BlockMoveLeft = false;
	m_BlockMoveUp = false;
	m_BlockMoveDown = false;
}

void dae::RecognizerEnemy::OnColl(const GameObject* other)
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

bool dae::RecognizerEnemy::DoDamage()
{
	--m_Health;
	if (m_Health <= 0)
	{
		m_Scene.Remove(m_pGameObject);
		return true;
	}
	return false;
}
