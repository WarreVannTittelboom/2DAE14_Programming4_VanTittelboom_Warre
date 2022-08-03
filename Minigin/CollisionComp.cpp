#include "MiniginPCH.h"
#include "CollisionComp.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

dae::CollisionComp::CollisionComp(GameObject* gameObject,float width, float height, bool active)
	: BaseComp(gameObject)
	, m_Width(width)
	, m_Height(height)
	, m_Active(active)
{
}

dae::CollisionComp::~CollisionComp()
{
	SceneManager::GetInstance().GetActiveScene().RemoveCollider(this);
}

void dae::CollisionComp::Initialize()
{
	m_Pos = glm::ivec2{ m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y };
}


void dae::CollisionComp::Update()
{
	m_Pos = glm::ivec2{ m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y };
}

bool dae::CollisionComp::CheckCollision(CollisionComp* pCollider) 
{
	Update();
	pCollider->Update();
	if (!pCollider->m_Active || !m_Active) { return false; }
	
	// If one rectangle is on left side of the other
	if ( (m_Pos.x + m_Width) < pCollider->m_pGameObject->GetWorldPosition().x || (pCollider->m_pGameObject->GetWorldPosition().x + pCollider->m_Width) < m_Pos.x)
	{
		return false;
	}

	// If one rectangle is under the other
	if (m_Pos.y > (pCollider->m_pGameObject->GetWorldPosition().y + m_Height) || pCollider->m_pGameObject->GetWorldPosition().y  > (m_Pos.y  + pCollider->m_Height) )
	{
		return false;
	}

	return true;
}
