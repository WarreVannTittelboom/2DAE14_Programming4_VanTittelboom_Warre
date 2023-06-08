#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		if (scene->m_IsActive)
		scene->Update();
	}
}

void dae::SceneManager::FixedUpdate(float fDT)
{
	for (auto& scene : m_Scenes)
	{
		if (scene->m_IsActive)
			scene->FixedUpdate(fDT);
	}
}

void dae::SceneManager::LateUpdate()
{
	for (auto& scene : m_Scenes)
	{
		if (scene->m_IsActive)
			scene->LateUpdate();
	}
}

void dae::SceneManager::Render()
{
	for(auto & scene : m_Scenes)
	{
		if (scene->m_IsActive)
			scene->Render();
	}
}

void dae::SceneManager::RemoveMarkedObjects()
{
	for (auto scene : m_Scenes)
	{
		scene->RemoveMarkedObjects();
	}
}
//void dae::SceneManager::CheckGoNextScene()
//{
//	for (auto& scene : m_Scenes)
//	{
//		if (scene->m_IsActive)
//		{
//			if (scene->m_TotalEnemyCount != 0 && scene->m_DeadEnemyCount == scene->m_TotalEnemyCount)
//			{
//				scene->m_DeadEnemyCount = 0;
//				SetScene("Level2");
//			}
//		}
//	}
//}

dae::SceneManager::~SceneManager()
{
	m_Scenes.clear();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	scene->Initialize();
	return *scene;
}

dae::Scene& dae::SceneManager::GetScene(const std::string& name)
{
	for (auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
			
			return *scene;
	}
	throw std::runtime_error("Scene not found");
}

dae::Scene& dae::SceneManager::GetActiveScene()
{
	for (auto& scene : m_Scenes)
	{
		if (scene->m_IsActive)

			return *scene;
	}
	throw std::runtime_error("Scene not found");
}


void dae::SceneManager::SetScene(const std::string& name)
{
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		if (m_Scenes[i]->GetName() == name)
		{
			m_Scenes[i]->m_IsActive = true;
			for (auto& scene : m_Scenes)
			{
				if (scene->GetName() != name)
					scene->m_IsActive = false;
			}
			return;
		}
	}
}
