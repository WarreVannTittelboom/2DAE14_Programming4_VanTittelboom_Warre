#pragma once
#include "BasicEnemy.h"
#include "TronObservers.h"
#include "Timer.h"
#include "TextureComp.h"
#include <random>

#define PI 3.14159265

dae::BasicEnemy::BasicEnemy(GameObject* gameObject, float x, float y, float w, float h, Scene& scene)
	:BaseComp(gameObject)
	,m_Scene(scene)
	,m_PosX(x)
	,m_PosY(y)
	,m_Width(w)
	,m_Height(h)
{
}

void dae::BasicEnemy::Initialize()
{
	GetGameObject()->SetPosition(m_PosX, -m_PosY);
	m_enemyHorizontalSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/EnemyTankHorizontal.png", (int)m_Width, (int)m_Height, false);
	GetGameObject()->AddComponent(m_enemyHorizontalSprite);
	m_enemyVerticalSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/EnemyTankVertical.png", (int)m_Width, (int)m_Height, true);
	GetGameObject()->AddComponent(m_enemyVerticalSprite);
	auto playercol = std::make_shared<dae::CollisionComp>(GetGameObject(), m_Width, m_Height, true);
	GetGameObject()->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	GetGameObject()->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new EnemyCollisionObserver());
}


void dae::BasicEnemy::Update()
{
	switch (m_CurrentState)
	{
	case RecognizerEnemyState::Wander:
		if (CheckPlayerInRange())
		{
			DoMoveToPlayer();
			m_CurrentState = RecognizerEnemyState::MoveToPlayer;
		}
		else
		{
			DoWander();
		}
		break;
	case RecognizerEnemyState::MoveToPlayer:
		if (!CheckPlayerInRange())
		{
			DoMoveToLastPlayerPos();
			m_CurrentState = RecognizerEnemyState::MoveToLastPlayerPos;
		}
		else
		{
			DoMoveToPlayer();
		}
		break;
	case RecognizerEnemyState::MoveToLastPlayerPos:
		if (CheckPlayerInRange())
		{
			DoMoveToPlayer();
			m_CurrentState = RecognizerEnemyState::MoveToPlayer;
		}
		else if (HasReachedLastPlayerPos())
		{
			DoWander();
			m_CurrentState = RecognizerEnemyState::Wander;
		}
		else
		{
			DoMoveToLastPlayerPos();
		}
		break;
	}

	if (m_ChangeDirMaxTime <= m_ChangeDirTimer)
	{
		RandomizeDirection();
		m_ChangeDirTimer = 0.f;
	}
	else
	{
		m_ChangeDirTimer += Timer::GetInstance().GetDeltaTime();
	}
	UpdateMovement();
}

void dae::BasicEnemy::OnColl(const GameObject* other)
{
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

void dae::BasicEnemy::ShootCannon(float degreesAngle)
{
	if (m_ShootCannonCooldown >= 1.f)
	{
		m_ShootCannonCooldown = 0.0f;
		auto bulletGo = std::make_shared<dae::GameObject>();
		float cosX = float(cos((degreesAngle) * (PI / 180.0f)));
		float sinY = float(sin((degreesAngle) * (PI / 180.0f)));
		auto bulletComp = std::make_shared<dae::EnemyBullet>(bulletGo.get(), GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y, cosX, sinY, m_Scene);
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
		GetGameObject()->SetPosition(-1000.f, -1000.f);
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

void dae::BasicEnemy::DoWander()
{
	m_Wander = true;
}

void dae::BasicEnemy::DoMoveToPlayer()
{
	m_Wander = false;
	m_TargetPosX = m_LastPlayerPosX;
	m_TargetPosY = m_LastPlayerPosY;
}

void dae::BasicEnemy::DoMoveToLastPlayerPos()
{
	m_Wander = false;
	m_TargetPosX = m_PlayerTargetPosX;
	m_TargetPosY = m_PlayerTargetPosY;
}

void dae::BasicEnemy::ColEdgeCases()
{
	float deltaTime = Timer::GetInstance().GetDeltaTime();
	if (m_Wander) { RandomizeDirection(); }
	if (m_BlockMoveLeft && !m_BlockMoveUp && !m_BlockMoveDown) {
		GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
		m_enemyHorizontalSprite->m_IsActive = false;
		m_enemyVerticalSprite->m_IsActive = true;
		m_enemyVerticalSprite->m_FlipHorizontal = false;
		m_enemyVerticalSprite->m_FlipVertical = false;
		ShootCannon(90.f);
	}
	else if (m_BlockMoveRight && !m_BlockMoveUp && !m_BlockMoveDown) {
		GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
		m_enemyHorizontalSprite->m_IsActive = false;
		m_enemyVerticalSprite->m_IsActive = true;
		m_enemyVerticalSprite->m_FlipHorizontal = false;
		m_enemyVerticalSprite->m_FlipVertical = false;
		ShootCannon(90.f);
	}
	else if (m_BlockMoveUp && !m_BlockMoveLeft && !m_BlockMoveRight) {
		GetGameObject()->SetPosition(GetGameObject()->GetPosition().x - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
		m_enemyHorizontalSprite->m_IsActive = true;
		m_enemyVerticalSprite->m_IsActive = false;
		m_enemyHorizontalSprite->m_FlipHorizontal = true;
		m_enemyHorizontalSprite->m_FlipVertical = false;
		ShootCannon(180.f);
	}
	else if (m_BlockMoveDown && !m_BlockMoveLeft && !m_BlockMoveRight) {
		GetGameObject()->SetPosition(GetGameObject()->GetPosition().x - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
		m_enemyHorizontalSprite->m_IsActive = true;
		m_enemyVerticalSprite->m_IsActive = false;
		m_enemyHorizontalSprite->m_FlipHorizontal = true;
		m_enemyHorizontalSprite->m_FlipVertical = false;
		ShootCannon(180.f);
	}
}

void dae::BasicEnemy::UpdateMovement()
{
	m_ShootCannonCooldown += Timer::GetInstance().GetDeltaTime();
	if (m_Wander)
	{
		float deltaTime = Timer::GetInstance().GetDeltaTime();
		if ((!m_BlockMoveLeft) && m_Direction == 0)
		{

			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = true;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
			ShootCannon(180.f);
		}
		else if ((!m_BlockMoveRight) && m_Direction == 1)
		{

			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
			ShootCannon(0.f);

		}
		else if ((!m_BlockMoveUp) && m_Direction == 2)
		{

			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = false;
			ShootCannon(90.f);

		}
		else if ((!m_BlockMoveDown) && m_Direction == 3)
		{

			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
			ShootCannon(270.f);

		}
		else
		{
			ColEdgeCases();
		}
		m_BlockMoveRight = false;
		m_BlockMoveLeft = false;
		m_BlockMoveUp = false;
		m_BlockMoveDown = false;
	}


	else
	{
		float valueDiffX{ 0.f };
		float valueDiffY{ 0.f };
		float diffX = m_TargetPosX - GetGameObject()->GetPosition().x;
		if (diffX < 0) { valueDiffX = diffX * -1; }
		else { valueDiffX = diffX; }
		float diffY = m_TargetPosY - GetGameObject()->GetPosition().y;
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
			ShootCannon(180.f);
		}
		else if (valueDiffX > valueDiffY && diffX > 0 && (!m_BlockMoveRight))
		{

			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().y, GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_IsActive = false;
			m_enemyHorizontalSprite.get()->m_FlipHorizontal = false;
			m_enemyHorizontalSprite.get()->m_FlipVertical = false;
			ShootCannon(0.f);

		}
		else if (valueDiffX < valueDiffY && diffY > 0 && (!m_BlockMoveUp))
		{

			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y + (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = false;
			ShootCannon(90.f);

		}
		else if (valueDiffX < valueDiffY && diffY < 0 && (!m_BlockMoveDown))
		{

			GetGameObject()->SetPosition(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y - (deltaTime * m_EnemySpeed), GetGameObject()->GetPosition().z);
			m_enemyHorizontalSprite.get()->m_IsActive = false;
			m_enemyVerticalSprite.get()->m_IsActive = true;
			m_enemyVerticalSprite.get()->m_FlipHorizontal = false;
			m_enemyVerticalSprite.get()->m_FlipVertical = true;
			ShootCannon(270.f);

		}
		else
		{
			ColEdgeCases();
		}
		m_BlockMoveRight = false;
		m_BlockMoveLeft = false;
		m_BlockMoveUp = false;
		m_BlockMoveDown = false;

	}
}

bool dae::BasicEnemy::HasReachedLastPlayerPos()
{
	m_StuckTimer += Timer::GetInstance().GetDeltaTime();
	float minRange = 60.f;
	float distance = float(sqrt(pow(GetGameObject()->GetPosition().x - m_LastPlayerPosX, 2) + pow(GetGameObject()->GetPosition().y - m_LastPlayerPosY, 2) * 1.0));
	if (distance <= minRange)
	{
		return true;
	}
	else if (m_StuckTimer >= m_MaxStuckTimer)
	{
		m_StuckTimer = 0.f;
		return true;
	}
	return false;
}

bool dae::BasicEnemy::CheckPlayerInRange()
{
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
			m_PlayerTargetPosX = x1;
			m_PlayerTargetPosY = y1;
		}
		else
		{
			m_PlayerTargetPosX = x2;
			m_PlayerTargetPosY = y2;
		}
	}
	else
	{
		if (players.size() > 0)
		{
			m_PlayerTargetPosX = players[0]->GetGameObject()->GetPosition().x;
			m_PlayerTargetPosY = players[0]->GetGameObject()->GetPosition().y;
		}
	}
	bool blocking = dae::TronGame::GetInstance().IsWallBetween(glm::vec2(m_PlayerTargetPosX, m_PlayerTargetPosY), glm::vec2(GetGameObject()->GetPosition().x, GetGameObject()->GetPosition().y));
	if (!blocking)
	{
		m_LastPlayerPosX = m_PlayerTargetPosX;
		m_LastPlayerPosY = m_PlayerTargetPosY;
		return true;
	}
	return false;
}

void dae::BasicEnemy::RandomizeDirection()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 3);
	m_Direction = dist(gen);
}
