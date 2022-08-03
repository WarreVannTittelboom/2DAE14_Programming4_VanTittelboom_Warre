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
		void Add(const std::shared_ptr<SceneObject>& object);
		void Remove(GameObject* object);
		std::string GetName() const { return m_Name; }

		void Initialize();
		void Update();
		void FixedUpdate(float fDT);
		void LateUpdate();
		void Render() const;
		void AddCollider(const std::shared_ptr<CollisionComp>& object);
		void RemoveCollider(CollisionComp* object);

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		bool m_IsActive = true;
	private:
		explicit Scene(const std::string& name);
		std::string m_Name;
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};

		CollisionManager m_CollManager;
	};

}
