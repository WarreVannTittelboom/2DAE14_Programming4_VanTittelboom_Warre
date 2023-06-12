#pragma once
#include "MiniginPCH.h"
#include "Observer.h"
#include "CollisionManager.h"
#include "CollisionComp.h"

void dae::CollisionManager::AddCollider(dae::CollisionComp* pCollider)
{
	m_pColliders.push_back(pCollider);
}

void dae::CollisionManager::RemoveCollider(dae::CollisionComp* pCollider)
{
	for (size_t i = 0; i < m_pColliders.size(); ++i)
	{
		if (pCollider == m_pColliders[i])
		{
			m_pColliders[i]->SetRemoved(true); // Set the removed flag to true
			m_pColliders[i] = m_pColliders.back();
			m_pColliders.pop_back();
			m_ShouldSkipLoop = true;
			break; // Exit the loop after removing the collider
		}
	}
}

void dae::CollisionManager::Update()
{
	for (size_t i{}; i < m_pColliders.size(); ++i)
	{
		auto pCollider = m_pColliders[i];
		if (pCollider->IsActive() && !pCollider->IsRemoved()) // Check if collider is active and not removed
		{
			for (size_t j{}; j < m_pColliders.size(); ++j)
			{
				if (m_ShouldSkipLoop)
					break;

				auto pOther = m_pColliders[j];
				if (pCollider == pOther || pOther->IsRemoved()) // Skip removed colliders
					continue;

				if (pCollider->CheckCollision(pOther))
				{
					if (pOther->GetGameObject())
					{
						pCollider->GetSubject()->Notify(pOther->GetGameObject(), pCollider->GetGameObject(), dae::Event::CollEvent);
					}
				}
			}
		}
	}
}
