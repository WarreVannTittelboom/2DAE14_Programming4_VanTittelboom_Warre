#pragma once
#include "MiniginPCH.h"
#include "SceneObject.h"
#include "Transform.h"



namespace dae
{
	class BaseComp;

	class GameObject final : public SceneObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void FixedUpdate(float fDT) override;
		void LateUpdate() override;
		void Render() const override;

		void AddComponent(const std::shared_ptr<BaseComp>& comp);
		template <typename T> T* GetComponent() const;
		template <typename T> std::vector<std::shared_ptr<BaseComp>>::const_iterator getCompIdx() const;
		template <typename T> bool RemoveComponent();
		bool RemoveComponent(std::shared_ptr<dae::BaseComp> comp);

		void SetLocalPos(const glm::vec3& pos);


	

		void SetParent(GameObject* pParent, bool keepWorldPos);

		
		

		
		void SetPosition(float x, float y);
		void SetPosition(float x, float y,float z);
		void SetPosition(int x, int y);
		void SetPosition(int x, int y, int z);
		

		std::vector<std::shared_ptr<BaseComp>> GetComponents() { return m_pComponents; }

		explicit GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		const glm::vec3& GetLocalPos() { return m_localPosition; };
		const glm::vec3& GetPosition() { return m_localPosition; };
		const glm::vec3 GetWorldPosition();
		void UpdateWorldPos();

		void SetPositionDirty()
		{
			m_PositionIsDirty = true;
			for (auto child : m_pChildren)
				child->SetPositionDirty();
		}

	private:

		void AddChild(GameObject* pChild) { m_pChildren.push_back(pChild); }
		void RemoveChild(GameObject* pChild) { m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), pChild), m_pChildren.end()); }
		
		std::vector<std::shared_ptr<BaseComp>> m_pComponents;
		
		GameObject* m_pParent;
		std::vector<GameObject*> m_pChildren;

		bool m_PositionIsDirty = true;

		glm::vec3 m_worldPosition;
		glm::vec3 m_localPosition;
		
	};


	template <typename T>
	T* GameObject::GetComponent() const
	{
		for (auto& component : m_pComponents)
		{
			T* compnt = dynamic_cast<T*>(component.get());
			
			if ((compnt != nullptr))
			{
				return compnt;
			}
		}
		return nullptr;
	}

	template <typename T>
	std::vector<std::shared_ptr<BaseComp>>::const_iterator GameObject::getCompIdx() const
	{
		return std::find_if(m_pComponents.begin(), m_pComponents.end(),[](std::shared_ptr<BaseComp> comp)
			{
				T* compnt = dynamic_cast<T*>(comp.get());
				
				if ((compnt != nullptr))
				{
					return true;
				}
				return false;
			});
	}

	template <typename T>
	bool GameObject::RemoveComponent()
	{
		std::vector<std::shared_ptr<BaseComp>>::const_iterator idx = getCompIdx<T>();
		m_pComponents.erase(idx);
		return true;
	}


}
