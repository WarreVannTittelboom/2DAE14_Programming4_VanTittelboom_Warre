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
#include <Font.h>
#include <TextComp.h>


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
	auto playercol = std::make_shared<dae::CollisionComp>(GetGameObject(), m_Width, m_Height, true);
	GetGameObject()->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	GetGameObject()->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new ButtonObserver());
}

void dae::Button::OnColl(const GameObject* other)
{
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
