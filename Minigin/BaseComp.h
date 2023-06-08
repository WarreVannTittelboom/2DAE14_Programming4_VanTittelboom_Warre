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
		const std::unique_ptr<Subject>& GetSubject() const { return m_pSubject; };
		GameObject* GetGameObject() const { return m_pGameObject; }

	protected:
		explicit BaseComp(GameObject* pOwner) : m_pGameObject(pOwner) { m_pSubject = std::make_unique<Subject>(); }
		std::unique_ptr<Subject> m_pSubject;
		
	private:
		GameObject* m_pGameObject;
	};
}

