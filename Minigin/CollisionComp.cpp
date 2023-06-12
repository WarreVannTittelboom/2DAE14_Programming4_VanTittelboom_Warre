#include "MiniginPCH.h"
#include "CollisionComp.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

dae::CollisionComp::CollisionComp(GameObject* gameObject, float width, float height, bool active)
	: BaseComp(gameObject)
	, m_Width(width)
	, m_Height(height)
	, m_Active(active)
	, m_Removed(false) // Initialize removed flag to false
{
}

dae::CollisionComp::~CollisionComp()
{
	SceneManager::GetInstance().GetActiveScene().RemoveCollider(this);
}

void dae::CollisionComp::Initialize()
{
	m_Pos = glm::ivec2{ GetGameObject()->GetWorldPosition().x, GetGameObject()->GetWorldPosition().y };
}

void dae::CollisionComp::Update()
{
	m_Pos = glm::ivec2{ GetGameObject()->GetWorldPosition().x, GetGameObject()->GetWorldPosition().y };
}

bool dae::CollisionComp::CheckCollision(CollisionComp* pCollider)
{
	if (pCollider != nullptr && !pCollider->IsRemoved()) // Check if collider is not removed
	{
		Update();
		pCollider->Update();
		if (!pCollider->IsActive() || !m_Active)
			return false;

		// If one rectangle is on the left side of the other
		if ((m_Pos.x + m_Width) < pCollider->GetGameObject()->GetWorldPosition().x || (pCollider->GetGameObject()->GetWorldPosition().x + pCollider->m_Width) < m_Pos.x)
		{
			return false;
		}

		// If one rectangle is under the other
		if (m_Pos.y > (pCollider->GetGameObject()->GetWorldPosition().y + m_Height) || pCollider->GetGameObject()->GetWorldPosition().y > (m_Pos.y + pCollider->m_Height))
		{
			return false;
		}

		return true;
	}
	return false;
}

void dae::CollisionComp::SetRemoved(bool removed)
{
	m_Removed = removed;
}

bool dae::CollisionComp::IsRemoved() const
{
	return m_Removed;
}
