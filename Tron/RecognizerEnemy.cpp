#pragma once
#include "RecognizerEnemy.h"
#include "TronObservers.h"
#include "Timer.h"
#include "PlayerTank.h"


dae::RecognizerEnemy::RecognizerEnemy(GameObject* gameObject, float x, float y, float w, float h,  Scene& scene)
	:BaseComp(gameObject)
	, m_Scene(scene)
	, m_PosX(x)
	, m_PosY(y)
	, m_Width(w)
	, m_Height(h)
	
{
}

dae::RecognizerEnemy::~RecognizerEnemy()
{
}

void dae::RecognizerEnemy::Initialize()
{
	GetGameObject()->SetPosition(m_PosX, -m_PosY);
	m_enemyHorizontalSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/rEnemyTankHorizontal.png", (int)m_Width, (int)m_Height, false);
	GetGameObject()->AddComponent(m_enemyHorizontalSprite);
	m_enemyVerticalSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/rEnemyTankVertical.png", (int)m_Width, (int)m_Height, true);
	GetGameObject()->AddComponent(m_enemyVerticalSprite);
	auto playercol = std::make_shared<dae::CollisionComp>(GetGameObject(), m_Width, m_Height, true);
	GetGameObject()->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	GetGameObject()->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new EnemyCollisionObserver());
}


void dae::RecognizerEnemy::Update()
{
	float playerPosX = 0.f;
	float playerPosY = 0.f;
	auto players = dae::SceneManager::GetInstance().GetActiveScene().FindObjectsOfType<dae::PlayerTank>();
	if (players.size() > 1)
	{
		float x1 = players[0]->GetGameObject()->GetPosition().x;
		float y1 = players[0]->GetGameObject()->GetPosition().y;
		float x2 = players[1]->GetGameObject()->GetPosition().x;
		float y2 = players[1]->GetGameObject()->GetPosition().y;
		auto dis1 = sqrt(pow(int(x1 - GetGameObject()->GetPosition().x), 2) + pow(int(y1 - GetGameObject()->GetPosition().y), 2) * 1.0);
		auto dis2 = sqrt(pow(int(x2 - GetGameObject()->GetPosition().x), 2) + pow(int(y2 - GetGameObject()->GetPosition().y), 2) * 1.0);
		if (dis2 > dis1)
		{
			playerPosX = x1;
			playerPosY = y1;
		}
		else
		{
			playerPosX = x2;
			playerPosY = y2;
		}
	}
	else
	{
		if (players.size() > 0)
		{
			playerPosX = players[0]->GetGameObject()->GetPosition().x;
			playerPosY = players[0]->GetGameObject()->GetPosition().y;
		}
	}
	float valueDiffX{ 0.f };
	float valueDiffY{ 0.f };
	float diffX = playerPosX - GetGameObject()->GetPosition().x;
	if (diffX < 0) { valueDiffX = diffX * -1; }
	else { valueDiffX = diffX; }
	float diffY = playerPosY - GetGameObject()->GetPosition().y;
	if (diffY < 0) { valueDiffY = diffY * -1; }
	else { valueDiffY = diffY; }
	float deltaTime = Timer::GetInstance().GetDeltaTime();
	if (valueDiffX > valueDiffY && diffX < 0 && (!m_BlockMoveLeft))
	{

		GetGameObject()->SetPosition(GetGameObject()->GetPosition().x - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
		m_enemyHorizontalSprite.get()->m_IsActive = true;
		m_enemyVerticalSprite.get()->m_IsActive = false;
		m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
		m_enemyHorizontalSprite.get()->m_FlipVertical = false;
	}
	else if (valueDiffX > valueDiffY && diffX > 0 && (!m_BlockMoveRight))
	{

		GetGameObject()->SetPosition(GetGameObject()->GetPosition().x + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
		m_enemyHorizontalSprite.get()->m_IsActive = true;
		m_enemyVerticalSprite.get()->m_IsActive = false;
		m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
		m_enemyHorizontalSprite.get()->m_FlipVertical = false;

	}
	else if (valueDiffX < valueDiffY && diffY > 0 && (!m_BlockMoveUp))
	{

		GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
		m_enemyHorizontalSprite.get()->m_IsActive = false;
		m_enemyVerticalSprite.get()->m_IsActive = true;
		m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
		m_enemyVerticalSprite.get()->m_FlipVertical = false;

	}
	else if (valueDiffX < valueDiffY && diffY < 0 && (!m_BlockMoveDown))
	{

		GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
		m_enemyHorizontalSprite.get()->m_IsActive = false;
		m_enemyVerticalSprite.get()->m_IsActive = true;
		m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
		m_enemyVerticalSprite.get()->m_FlipVertical = true;

	}
	else
	{
		if (m_BlockMoveLeft && (!m_BlockMoveUp))
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = false;

		}
		else if (m_BlockMoveLeft && m_BlockMoveUp && (!m_BlockMoveDown))
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
		}
		else if (m_BlockMoveLeft && (!m_BlockMoveRight))
		{

			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveRight && (!m_BlockMoveUp))
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveRight && m_BlockMoveUp && (!m_BlockMoveDown))
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
		}
		else if (m_BlockMoveRight && (!m_BlockMoveLeft))
		{

			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}

		else if (m_BlockMoveUp && (!m_BlockMoveLeft))
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveUp && m_BlockMoveLeft && (!m_BlockMoveRight))
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveUp && (!m_BlockMoveDown))
		{

			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
		}

		else if (m_BlockMoveDown && (!m_BlockMoveLeft))
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveDown && m_BlockMoveLeft && (!m_BlockMoveRight))
		{
			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
		}
		else if (m_BlockMoveDown && (!m_BlockMoveUp))
		{

			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
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

bool dae::RecognizerEnemy::DoDamage()
{
	--m_Health;
	if (m_Health <= 0)
	{
		dae::TronGame::GetInstance().m_Score += 250;
		GetGameObject()->SetPosition(1000.f, 1000.f);
		//GetGameObject()->MarkDestroy();
		m_Scene.m_DeadEnemyCount += 1;
		if (m_Scene.m_TotalEnemyCount != 0 && m_Scene.m_DeadEnemyCount == m_Scene.m_TotalEnemyCount)
		{
			m_Scene.m_DeadEnemyCount = 0;
			dae::TronGame::GetInstance().ResetLevelForNext();
			dae::TronGame::GetInstance().LoadNextScene();

		}
		return true;
	}
	return false;
}
