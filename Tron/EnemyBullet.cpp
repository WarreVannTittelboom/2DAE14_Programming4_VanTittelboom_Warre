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
	auto playerBulletCol = std::make_shared<dae::CollisionComp>(GetGameObject(), 8.f, 8.f, true);
	GetGameObject()->AddComponent(playerBulletCol);
	m_Scene.AddCollider(playerBulletCol);
	auto playerBulletSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/EnemyBullet.png", 8, 8, true);
	GetGameObject()->AddComponent(playerBulletSprite);
	GetGameObject()->SetPosition(m_StartPosX + 16, m_StartPosY - 16);
	GetGameObject()->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new EnemyBulletObserver());
	GetGameObject()->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new PlayerBulletObserver());
}

void dae::EnemyBullet::Update()
{
	float deltaTime = Timer::GetInstance().GetDeltaTime();
	float newX = GetGameObject()->GetWorldPosition().x + m_CosX * m_BulletSpeed * deltaTime;
	float newY = GetGameObject()->GetWorldPosition().y + m_SinY * m_BulletSpeed * deltaTime;
	GetGameObject()->SetPosition(newX, newY);

}

void dae::EnemyBullet::OnColl(const GameObject* other)
{
	if (other->GetComponent<dae::Wall>())
	{
		GetGameObject()->MarkDestroy();
	}
}
