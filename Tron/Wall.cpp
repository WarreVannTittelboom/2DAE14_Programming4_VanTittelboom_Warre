#include "Wall.h"
#include "TextureComp.h"
#include "TronObservers.h"
#include "TextureComp.h"


dae::Wall::Wall(GameObject* gameObject, float x, float y, float w, float h, const std::string& filename, Scene& scene)
	: BaseComp(gameObject)
	, m_Scene(scene)
	, m_PosX(x)
	, m_PosY(y)
	, m_Width(w)
	, m_Height(h)
	, m_FileName(filename)
{
}


void dae::Wall::Initialize()
{
	GetGameObject()->SetPosition(m_PosX, -m_PosY);
	auto sprite = std::make_shared<dae::TextureComp>(GetGameObject(), m_FileName, (int)m_Width, (int)m_Height, true);
	GetGameObject()->AddComponent(sprite);
	auto playercol = std::make_shared<dae::CollisionComp>(GetGameObject(), m_Width, m_Height, true);
	GetGameObject()->AddComponent(playercol);
	m_Scene.AddCollider(playercol);
	GetGameObject()->GetComponent<CollisionComp>()->GetSubject()->AddObserver(new CollisionObserver());
}