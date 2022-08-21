#include "PlayerBullet.h"
#include <CollisionComp.h>
#include "PlayerTank.h"
#include <Timer.h>
#include <Scene.h>
#include <SceneManager.h>
#include "TronObservers.h"
#include "Wall.h"
#include "RecognizerEnemy.h"
#include <Font.h>
#include <TextComp.h>

dae::PlayerBullet::PlayerBullet(GameObject* gameObject, float x, float y,float cosx,float siny,Scene& scene,unsigned int id)
	: BaseComp(gameObject)
	, m_Scene(scene)
	, m_StartPosX(x)
	, m_StartPosY(y)
	, m_CosX(cosx)
	, m_SinY(siny)
	,m_Id(id)
{
}

dae::PlayerBullet::~PlayerBullet()
{
}

void dae::PlayerBullet::Initialize()
{
	auto playerBulletCol = std::make_shared<dae::CollisionComp>(m_pGameObject, 8.f, 8.f, true);
	m_pGameObject->AddComponent(playerBulletCol);
	m_Scene.AddCollider(playerBulletCol);
	if (m_Id == 1)
	{
		auto playerBulletSprite = std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/Player2Bullet.png", 8, 8, true);
		m_pGameObject->AddComponent(playerBulletSprite);
		m_pGameObject->SetPosition(m_StartPosX + 16, m_StartPosY - 16);
		m_pGameObject->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new PlayerBulletObserver());
	}
	else
	{
		auto playerBulletSprite = std::make_shared<dae::TextureComp>(m_pGameObject, "../Data/PlayerBullet.png", 8, 8, true);
		m_pGameObject->AddComponent(playerBulletSprite);
		m_pGameObject->SetPosition(m_StartPosX + 16, m_StartPosY - 16);
		m_pGameObject->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new PlayerBulletObserver());
	}
}

void dae::PlayerBullet::Update()
{
	float deltaTime = Timer::GetInstance().GetDeltaTime();
	float newX = m_pGameObject->GetWorldPosition().x + m_CosX * m_BulletSpeed * deltaTime;
	float newY = m_pGameObject->GetWorldPosition().y + m_SinY * m_BulletSpeed * deltaTime;
	m_pGameObject->SetPosition(newX, newY);
	if (m_BounceCount >= 6)
	{
		m_Scene.Remove(m_pGameObject);
	}
	
}

void dae::PlayerBullet::Render() const
{
}

void dae::PlayerBullet::OnColl(const GameObject* other)
{
	if (auto pWall = other->GetComponent<dae::Wall>())
	{
		++m_BounceCount;
		int x[] = { (int)pWall->m_PosX - (int)m_pGameObject->GetPosition().x, (int)pWall->m_PosX + (int)pWall->m_Width - (int)m_pGameObject->GetPosition().x, (int)pWall->m_PosY + (int)m_pGameObject->GetPosition().y + (int)pWall->m_Height, (int)pWall->m_PosY + (int)m_pGameObject->GetPosition().y};
		int len = sizeof(x) / sizeof(x[0]); 
		if (x[0] < 0)
		{
			x[0] *= -1;
		}
		if (x[1] < 0)
		{
			x[1] *= -1;
		}
		if (x[2] < 0)
		{
			x[2] *= -1;
		}
		if (x[3] < 0)
		{
			x[3] *= -1;
		}
		if (len > 0) {
			int smallest = x[0]; 

			for (int i = 1; i < len; i++) {
				if (smallest > x[i]) {
					smallest = x[i]; 
				}
			}
			if (smallest == x[0])
			{
				m_CosX *= -1;
			}
			else if (smallest == x[1])
			{
				m_CosX *= -1;
			}
			else if (smallest == x[2])
			{
				m_SinY *= -1;
			}
			else if (smallest == x[3])
			{
				m_SinY *= -1;
			}
		}
	}
	else if (auto pTank = other->GetComponent<dae::PlayerTank>())
	{
		if(m_Id != pTank->GetId() && (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "versus1" || dae::SceneManager::GetInstance().GetActiveScene().GetName() == "versus2" || dae::SceneManager::GetInstance().GetActiveScene().GetName() == "versus3"))
	{
			if (!((dae::SceneManager::GetInstance().GetActiveScene().GetName() == "Menu") || (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "gameoverscene")))
			{
			auto text = std::make_shared<dae::GameObject>();
			auto font = std::make_shared<dae::Font>("../Data/Lingua.otf", 40);
			auto textcomp = std::make_shared<dae::TextComp>(text.get(), "Player " + std::to_string((m_Id + 1)) + " won", font);
			textcomp->SetPos(185, 270);
			text->AddComponent(textcomp);
			dae::SceneManager::GetInstance().GetScene("gameoverscene").Add(text);

			dae::SceneManager::GetInstance().SetScene("gameoverscene");
			}
	}
	}
	else if (auto pEnemy = other->GetComponent<dae::BasicEnemy>())
	{
		if (pEnemy->DoDamage())
		{
			
		}
		m_Scene.Remove(m_pGameObject);
	}
	else if (auto pEnemyspecial = other->GetComponent<dae::RecognizerEnemy>())
	{
		if (pEnemyspecial->DoDamage())
		{
		
		}
		m_Scene.Remove(m_pGameObject);
	}
}
