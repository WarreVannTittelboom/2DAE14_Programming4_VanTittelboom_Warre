#pragma once
#include "MiniginPCH.h"
#include "Observer.h"
#include "CollisionManager.h"
#include "CollisionComp.h"

void dae::CollisionManager::AddCollider(dae::CollisionComp* pCollider)
{
	m_pColliders.push_back(pCollider);
}

void dae::CollisionManager::Update()
{
	for (auto pCollider : m_pColliders)
	{
		if (pCollider->m_Active)
		{
			for (auto pOther : m_pColliders)
			{
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
