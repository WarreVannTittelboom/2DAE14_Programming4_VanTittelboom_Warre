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


		
		void AddToChildren(const std::shared_ptr<GameObject>& child);
		std::vector<std::shared_ptr<GameObject>> GetChildren() const { return m_Children; }

		void SetParent(GameObject* parent);
		GameObject* GetParent() { return m_Parent; }
		
		

		glm::vec3 GetWorldPosition();
		void SetPosition(float x, float y);
		void SetPosition(float x, float y,float z);
		void SetPosition(int x, int y);
		void SetPosition(int x, int y, int z);
		glm::vec3 GetPosition() const { return m_Transform.GetPosition(); }
		const Transform& GetTransform() const { return m_Transform; }

		std::vector<std::shared_ptr<BaseComp>> GetComponents() { return m_pComponents; }

		explicit GameObject();
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		
		std::vector<std::shared_ptr<BaseComp>> m_pComponents;
		
		GameObject* m_Parent;
		std::vector<std::shared_ptr<GameObject>> m_Children;
		
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
