#pragma once
#include "EnemyBullet.h"
#include <CollisionComp.h>
#include <Timer.h>
#include <Scene.h>
#include <SceneManager.h>
#include "TronObservers.h"
#include "Wall.h"




dae::EnemyBullet::EnemyBullet(GameObject* gameObject, float x, float y, float cosx, float siny, Scene& scene)
	: BaseComp(gameObject)
	, m_Scene(scene)
	, m_StartPosX(x)
	, m_StartPosY(y)
	, m_CosX(cosx)
	, m_SinY(siny)
{
}

dae::EnemyBullet::~EnemyBullet()
{
}

void dae::EnemyBullet::Initialize()
{
	auto playerBulletCol = std::make_shared<dae::CollisionComp>(m_pGameObject, 8.f, 8.f, true);
	m_pGameObject->AddComponent(playerBulletCol);
	m_Scene.AddCollider(playerBulletCol);
	auto playerBulletSprite = std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/PlayerBullet.png", 8, 8, true);
	m_pGameObject->AddComponent(playerBulletSprite);
	m_pGameObject->SetPosition(m_StartPosX + 16, m_StartPosY - 16);
	m_pGameObject->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new EnemyBulletObserver());
	m_pGameObject->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new PlayerBulletObserver());
}

void dae::EnemyBullet::Update()
{
	float deltaTime = Timer::GetInstance().GetDeltaTime();
	float newX = m_pGameObject->GetWorldPosition().x + m_CosX * m_BulletSpeed * deltaTime;
	float newY = m_pGameObject->GetWorldPosition().y + m_SinY * m_BulletSpeed * deltaTime;
	m_pGameObject->SetPosition(newX, newY);

}

void dae::EnemyBullet::OnColl(const GameObject* other)
{
	if (other->GetComponent<dae::Wall>())
	{
		m_Scene.Remove(m_pGameObject);
	}
}
