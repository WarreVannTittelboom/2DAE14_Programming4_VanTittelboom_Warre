#include "Button.h"
#include "TronGame.h"
#include "TronObservers.h"

dae::Button::Button(GameObject* gameObject, float w, float h)
	: BaseComp(gameObject)
	, m_Scene(dae::SceneManager::GetInstance().GetActiveScene())
	, m_Width(w)
	, m_Height(h)
{
}

void dae::Button::Initialize()
{
	auto playercol = std::make_shared<dae::CollisionComp>(GetGameObject(), m_Width, m_Height, true);
	GetGameObject()->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	GetGameObject()->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new ButtonObserver());
}

void dae::Button::OnColl(const GameObject* other)
{
	dae::TronGame::GetInstance().m_LivesP1 = 3;
	dae::TronGame::GetInstance().m_LivesP2 = 3;
	if (GetGameObject()->GetPosition().x < 160.f)
	{
		dae::SceneManager::GetInstance().SetScene("coop1");
		
	}
	else if (GetGameObject()->GetPosition().x >  290.f)
	{
		dae::SceneManager::GetInstance().SetScene("versus1");
	}
	else
	{
		dae::SceneManager::GetInstance().SetScene("solo1");
	}
}
