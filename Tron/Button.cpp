#include "Button.h"
#include <TextureComp.h>
#include "PlayerTank.h"
#include <CollisionComp.h>
#include <Scene.h>
#include <map>
#include <InputManager.h>
#include "TronGame.h"
#include <TextureComp.h>
#include "PlayerCommands.h"
#include <Timer.h>
#include "PlayerBullet.h"
#include <math.h>  // for sin and cos
#include <GameObject.h>
#include <Scene.h>
#include <SceneManager.h>
#include<SceneObject.h>
#include "TronObservers.h"


dae::Button::Button(GameObject* gameObject, float w, float h)
	: BaseComp(gameObject)
	, m_Scene(dae::SceneManager::GetInstance().GetActiveScene())
	, m_Width(w)
	, m_Height(h)
{
}

dae::Button::~Button()
{
}

void dae::Button::Initialize()
{
	auto playercol = std::make_shared<dae::CollisionComp>(m_pGameObject, m_Width, m_Height, true);
	m_pGameObject->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	m_pGameObject->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new ButtonObserver());
}

void dae::Button::OnColl(const GameObject* other)
{
	if (m_pGameObject->GetPosition().x < 160.f)
	{
		dae::SceneManager::GetInstance().SetScene("coop1");
	}
	else if (m_pGameObject->GetPosition().x >  290.f)
	{
		dae::SceneManager::GetInstance().SetScene("versus1");
	}
	else
	{
		dae::SceneManager::GetInstance().SetScene("solo1");
	}
}
