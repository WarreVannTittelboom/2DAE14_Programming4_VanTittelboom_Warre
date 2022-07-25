#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseComp.h"
#include "Renderer.h"
using namespace dae;


GameObject::GameObject() : m_Parent(nullptr)
{
	auto screenSize = Renderer::GetInstance().GetScreenSize();
	m_Transform.SetPosition(0, (float)(-screenSize.y), 0);
}

void dae::GameObject::Initialize()
{
	for (auto& comp : m_pComponents)
	{
		comp->Initialize();
	}
}

void dae::GameObject::Update()
{
	for (auto& comp : m_pComponents)
	{
		comp.get()->Update();
	}
}

void dae::GameObject::FixedUpdate(float fDT)
{
	for (auto& comp : m_pComponents)
	{
		comp.get()->FixedUpdate(fDT);
	}

}

void dae::GameObject::LateUpdate()
{
	for (auto& comp : m_pComponents)
	{
		comp.get()->LateUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (auto& comp : m_pComponents)
	{
		comp.get()->Render();
	}
}

void GameObject::AddComponent(const std::shared_ptr<BaseComp>& comp)
{
	m_pComponents.push_back(comp);
	comp->SetGameObject(this);
}

bool GameObject::RemoveComponent(std::shared_ptr<dae::BaseComp> comp)
{
	m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), comp), m_pComponents.end());
	return true;
}

void GameObject::SetParent(GameObject* parent)
{
	m_Parent = parent;
}

void GameObject::AddToChildren(const std::shared_ptr<GameObject>& child)
{
	child->SetParent(this);
	m_Children.push_back(child);
}

const glm::vec3 GameObject::GetWorldPosition()
{
	if (m_Parent != nullptr)
	{
		return m_Parent->GetWorldPosition() + m_Transform.GetPosition();
	}
	return m_Transform.GetPosition();
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_Transform.SetPosition(x, y, z);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, m_Transform.GetPosition().z);
}

void dae::GameObject::SetPosition(int x, int y, int z)
{
	m_Transform.SetPosition((float)x, (float)y, (float)z);
}


void dae::GameObject::SetPosition(int x, int y)
{
	m_Transform.SetPosition((float)x, (float)y, m_Transform.GetPosition().z);
}