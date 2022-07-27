#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
	object->Initialize();
}
void Scene::Remove(const std::shared_ptr<GameObject>& object)
{
	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
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

