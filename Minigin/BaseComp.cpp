#include "MiniginPCH.h"
#include "BaseComp.h"
#include "GameObject.h"

dae::BaseComp::BaseComp(GameObject* gameObject)
	: m_pGameObject(gameObject)
{
	m_pSubject = std::make_unique<Subject>();
}

dae::GameObject* dae::BaseComp::GetGameObject() const
{
	return m_pGameObject;
}

void dae::BaseComp::SetGameObject(GameObject* object)
{
	m_pGameObject = object;
}


