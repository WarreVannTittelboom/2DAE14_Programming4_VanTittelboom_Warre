#pragma once
#include "MiniginPCH.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "CollisionComp.h"
#include "CollisionManager.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void Remove(GameObject* object);
		std::string GetName() const { return m_Name; }

		void Initialize();
		void Update();
		void FixedUpdate(float fDT);
		void LateUpdate();
		void Render() const;
		void AddCollider(const std::shared_ptr<CollisionComp>& object);
		void RemoveCollider(CollisionComp* object);
		void RemoveMarkedObjects();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		template<typename T>
		inline T* FindObjectOfType() const
		{
			std::vector<GameObject*> gameObjects;
			for (unsigned int i = 0; m_Objects.size() > i; ++i)
			{
				GameObject* curr = static_cast<GameObject*>(m_Objects[i].get());
				gameObjects.push_back(curr);
			}
			for (auto object : gameObjects)
			{
				auto objOfType = object->GetComponent<T>();
				if (objOfType)
				{
					return objOfType;
				}
			}
			return nullptr;
		}

		template<typename T>
		inline std::vector<T*> FindObjectsOfType() const
		{
			std::vector<T*> objects;

			std::vector<GameObject*> gameObjects; 
			for (unsigned int i = 0; m_Objects.size() > i; ++i)
			{
				GameObject* curr = static_cast<GameObject*>(m_Objects[i].get());
				gameObjects.push_back(curr);
			}
			for (auto object : gameObjects)
			{
				auto objOfType = object->GetComponent<T>();
				if (objOfType)
				{
					objects.push_back(objOfType);
				}
			}
			return objects;
		}

		bool m_IsActive = true;

		int m_DeadEnemyCount = 0;
		int m_TotalEnemyCount = 0;

		std::string m_FileName;
	private:
		explicit Scene(const std::string& name);
		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector < GameObject*> m_DestroyMarkedObjects{};

		CollisionManager m_CollManager;
	};

}
