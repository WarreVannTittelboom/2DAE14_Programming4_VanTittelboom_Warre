#include "PlayerBullet.h"
#include <CollisionComp.h>
#include "PlayerTank.h"
#include <Timer.h>
#include <SceneManager.h>
#include "TronObservers.h"
#include "Wall.h"
#include "RecognizerEnemy.h"
#include <Font.h>
#include <TextComp.h>
#include "HighScoreMenu.h"

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
	auto playerBulletCol = std::make_shared<dae::CollisionComp>(GetGameObject(), 8.f, 8.f, true);
	GetGameObject()->AddComponent(playerBulletCol);
	m_Scene.AddCollider(playerBulletCol);
	if (m_Id == 2)
	{
		auto playerBulletSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/Player2Bullet.png", 8, 8, true);
		GetGameObject()->AddComponent(playerBulletSprite);
		GetGameObject()->SetPosition(m_StartPosX + 16, m_StartPosY - 16);
		GetGameObject()->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new PlayerBulletObserver());
	}
	else
	{
		auto playerBulletSprite = std::make_shared<dae::TextureComp>(GetGameObject(), "../Data/PlayerBullet.png", 8, 8, true);
		GetGameObject()->AddComponent(playerBulletSprite);
		GetGameObject()->SetPosition(m_StartPosX + 16, m_StartPosY - 16);
		GetGameObject()->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new PlayerBulletObserver());
	}
}

void dae::PlayerBullet::Update()
{
	{ 
	float deltaTime = Timer::GetInstance().GetDeltaTime();
	float newX = GetGameObject()->GetWorldPosition().x + m_CosX * m_BulletSpeed * deltaTime;
	float newY = GetGameObject()->GetWorldPosition().y + m_SinY * m_BulletSpeed * deltaTime;
	GetGameObject()->SetPosition(newX, newY);
	if (m_BounceCount >= 6)
	{
		//GetGameObject()->MarkDestroy();
		GetGameObject()->SetPosition(200, 200);
	}
	}
	
}

void dae::PlayerBullet::Render() const
{
}

void dae::PlayerBullet::OnColl(const GameObject* other)
{
	{ 
	if (auto pTank = other->GetComponent<dae::PlayerTank>())
	{
		if (m_Id != pTank->GetId() && (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "versus1" || dae::SceneManager::GetInstance().GetActiveScene().GetName() == "versus2" || dae::SceneManager::GetInstance().GetActiveScene().GetName() == "versus3"))
		{
			if (!((dae::SceneManager::GetInstance().GetActiveScene().GetName() == "Menu") || (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "gameoverscene")))
			{
				if (pTank->GetId() == 1)
				{
					dae::TronGame::GetInstance().m_LivesP1 -= 1;
				}
				else if (pTank->GetId() == 2)
				{
					dae::TronGame::GetInstance().m_LivesP2 -= 1;
				}

				if (dae::TronGame::GetInstance().m_LivesP1 < 0 || dae::TronGame::GetInstance().m_LivesP2 < 0)
				{
					dae::TronGame::GetInstance().m_LivesP2 = 3;
					dae::TronGame::GetInstance().m_LivesP1 = 3;
					dae::TronGame::GetInstance().ResetLevelForNext();
					dae::SceneManager::GetInstance().SetScene("gameoverscene");
					dae::SceneManager::GetInstance().GetActiveScene().FindObjectOfType<dae::TextComp>()->SetText("Player " + std::to_string((m_Id)) + " won");
					dae::SceneManager::GetInstance().GetActiveScene().FindObjectOfType<dae::HighScoreMenu>()->LoadScores();
				}
				else 
				{
					dae::TronGame::GetInstance().ResetLevelForNext();
					dae::TronGame::GetInstance().LoadNextScene();
				}
			}
		}
	}
	else if (auto pWall = other->GetComponent<dae::Wall>())
	{
		++m_BounceCount;
		int x[] = { (int)pWall->m_PosX - (int)GetGameObject()->GetPosition().x, (int)pWall->m_PosX + (int)pWall->m_Width - (int)GetGameObject()->GetPosition().x, (int)pWall->m_PosY + (int)GetGameObject()->GetPosition().y + (int)pWall->m_Height, (int)pWall->m_PosY + (int)GetGameObject()->GetPosition().y};
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
	 
	else if (auto pEnemy = other->GetComponent<dae::BasicEnemy>())
	{
		if (pEnemy->DoDamage())
		{
			
		}
		GetGameObject()->SetPosition(200, 200);
	}
	else if (auto pEnemyspecial = other->GetComponent<dae::RecognizerEnemy>())
	{
		if (pEnemyspecial->DoDamage())
		{
		
		}
		GetGameObject()->SetPosition(200, 200);
	}
	}
}
