#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "BaseComp.h"
#include "Scene.h"
using namespace dae;


GameObject::GameObject() : m_pParent(nullptr)
{
	auto screenSize = Renderer::GetInstance().GetScreenSize();
	SetPosition(0.f, (float)(-screenSize.y));
}

dae::GameObject::~GameObject()
{
	
	m_pComponents.clear();
	m_pComponents = std::vector<std::shared_ptr<BaseComp>>();
	for (auto child : m_pChildren)
	{
		delete child;
		child = nullptr;
	}
	m_pChildren.clear();
}

void dae::GameObject::UpdateWorldPos()
{
	if (m_PositionIsDirty)
	{
		if (m_pParent == nullptr)
		{
			m_worldPosition = m_localPosition;
		}
		else
		{
			m_worldPosition = m_pParent->GetWorldPosition() + m_localPosition;
		}
	}
	m_PositionIsDirty = false;
}

void dae::GameObject::Initialize()
{
	for(size_t i = 0; i <  m_pComponents.size(); i++)
	{
		m_pComponents[i]->Initialize();
	}
}

void dae::GameObject::Update()
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Update();
	}
	if (m_pChildren.size() != 0)
	{
		for (auto child : m_pChildren)
		{
			child->Update();
		}
	}
}

void dae::GameObject::FixedUpdate(float fDT)
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->FixedUpdate(fDT);
	}
	if (m_pChildren.size() != 0)
	{
		for (auto child : m_pChildren)
		{
			child->FixedUpdate(fDT);
		}
	}
}

void dae::GameObject::LateUpdate()
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->LateUpdate();
	}
	if (m_pChildren.size() != 0)
	{
		for (auto child : m_pChildren)
		{
			child->LateUpdate();
		}
	}
}

void dae::GameObject::Render() const
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Render();
	}
	if (m_pChildren.size() != 0)
	{
		for (auto child : m_pChildren)
		{
			child->Render();
		}
	}
}

void GameObject::AddComponent(const std::shared_ptr<BaseComp>& comp)
{
	m_pComponents.push_back(comp);
}

bool GameObject::RemoveComponent(std::shared_ptr<dae::BaseComp> comp)
{
	m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), comp), m_pComponents.end());
	return true;
}

void GameObject::SetLocalPos(const glm::vec3& pos)
{
	m_localPosition = pos;
	SetPositionDirty();
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPos)
{
	if (pParent == nullptr)
		SetLocalPos(GetWorldPosition());
	else
	{
		if (keepWorldPos)
			SetLocalPos(GetLocalPos() - pParent->GetWorldPosition());
		SetPositionDirty();
	}
	// If it had previous parent, remove itself from it
	if (m_pParent) m_pParent->RemoveChild(this);

	// Set new parent and add itself as child to it
	m_pParent = pParent;
	if (m_pParent) m_pParent->AddChild(this);
}

const glm::vec3 GameObject::GetWorldPosition()
{
	if (m_PositionIsDirty)
	{
		UpdateWorldPos();
	}
	return m_worldPosition;
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	SetLocalPos(glm::vec3(x, y, z));
}

void dae::GameObject::SetPosition(float x, float y)
{
	SetLocalPos(glm::vec3(x, y,0.f));
}

void dae::GameObject::SetPosition(int x, int y, int z)
{
	SetLocalPos(glm::vec3((float)x, (float)y, (float)z));
}

void dae::GameObject::MarkDestroy()
{
	m_MarkedForDestroy = true;
	for (auto child : m_pChildren)
	{
		child->SetMarkedForDestroy();
	}
	dae::SceneManager::GetInstance().GetActiveScene().Remove(this);
}


void dae::GameObject::SetPosition(int x, int y)
{
	SetLocalPos(glm::vec3((float)x, (float)y, 0.f));
}