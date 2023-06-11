#include "Teleporter.h"
#include "PlayerTank.h"
#include <CollisionComp.h>
#include <map>
#include <InputManager.h>
#include "TronGame.h"
#include <TextureComp.h>
#include "PlayerCommands.h"
#include <Timer.h>
#include "PlayerBullet.h"
#include <math.h>  // for sin and cos
#include <SceneManager.h>
#include<SceneObject.h>
#include "TronObservers.h"


dae::Teleporter::Teleporter(GameObject* gameObject, float x, float y, float w, float h, const std::string& filename, std::shared_ptr<GameObject> playerTank, Scene& scene)
	: BaseComp(gameObject)
	, m_Scene(scene)
	, m_PosX(x)
	, m_PosY(y)
	, m_Width(w)
	, m_Height(h)
	, m_FileName(filename)
	, m_PlayerTank(playerTank)
{
}


void dae::Teleporter::Initialize()
{
	GetGameObject()->SetPosition(m_PosX, -m_PosY);
	auto sprite = std::make_shared<dae::TextureComp>(GetGameObject(), m_FileName, (int)m_Width, (int)m_Height, true);
	GetGameObject()->AddComponent(sprite);
	auto playercol = std::make_shared<dae::CollisionComp>(GetGameObject(), m_Width, m_Height, true);
	GetGameObject()->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	GetGameObject()->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new TeleportCollisionObserver(m_PlayerTank));
}


void dae::Teleporter::OnColl(const GameObject* other)
{
	
}