#pragma once
#pragma warning(disable:4100)
#include "GameObject.h"
#include "Subject.h"
namespace dae
{
	class GameObject;

	class BaseComp
	{
	public:
		BaseComp(GameObject* gameObject);
		virtual ~BaseComp() = default;
		BaseComp(const BaseComp& other) = delete;
		BaseComp(BaseComp&& other) = delete;
		BaseComp& operator=(const BaseComp& other) = delete;
		BaseComp& operator=(BaseComp&& other) = delete;

		virtual void Initialize() {};
		virtual void Update() {};
		virtual void FixedUpdate(float fDT) {};
		virtual void LateUpdate() {};
		virtual void Render() const {};
		virtual void OnColl(const GameObject* other) {};

		void SetGameObject(GameObject* object);
		GameObject* GetGameObject() const;

		const std::unique_ptr<Subject>& GetSubject() const { return m_pSubject; };

	protected:
		GameObject* m_pGameObject = nullptr;
		std::unique_ptr<Subject> m_pSubject;
	};
}

