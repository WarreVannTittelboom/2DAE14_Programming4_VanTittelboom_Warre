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
			m_pColliders[i] = m_pColliders.back();
			m_pColliders.pop_back();
			m_ShouldSkipLoop = true;
		}
	}
}

void dae::CollisionManager::Update()
{
	m_ShouldSkipLoop = false;

	for (size_t i{}; i < m_pColliders.size(); ++i)
	{
		auto pCollider = m_pColliders[i];
		if (pCollider->m_Active)
		{
			for (size_t j{}; j < m_pColliders.size(); ++j)
			{
				if (m_ShouldSkipLoop) 
				{
					m_ShouldSkipLoop = false;
					break;
				}
				
				auto pOther = m_pColliders[j];
				if (pCollider == pOther) { continue; }

				if (pCollider->CheckCollision(pOther))
				{ 
					if (pOther->GetGameObject()) 
					{ 
						pCollider->GetSubject()->Notify(pOther->GetGameObject(),pCollider->GetGameObject(), dae::Event::CollEvent);
					}
				}
			}
		}
	}
}
