#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	m_Objects.clear();
}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	object->Initialize();
}
void Scene::Remove(GameObject*  object)
{
	m_DestroyMarkedObjects.push_back(object);
	
}

void dae::Scene::RemoveMarkedObjects()
{
	for (int i{}; i < (int)m_DestroyMarkedObjects.size(); ++i)
	{
		for (size_t j = 0; j < m_Objects.size(); ++j)
		{
			if (m_Objects[j].get() == m_DestroyMarkedObjects[i])
			{
		
				m_Objects[j] = m_Objects.back();
				m_Objects.pop_back();
			}
		}
	}
	
}



void dae::Scene::Initialize()
{
	for (auto& object : m_Objects)
	{
		object->Initialize();
	}
}


void Scene::Update()
{
	m_CollManager.Update();
	for(size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Update();
	}
}

void Scene::FixedUpdate(float fDT)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(fDT);
	}
}

void Scene::LateUpdate()
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
	}
}
void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void dae::Scene::AddCollider(const std::shared_ptr<CollisionComp>& object)
{
	m_CollManager.AddCollider(object.get());
}

void dae::Scene::RemoveCollider(CollisionComp* object)
{
	m_CollManager.RemoveCollider(object);
}

