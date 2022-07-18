#pragma once
#pragma warning(disable:4100)
#include "GameObject.h"
namespace dae
{
	class GameObject;

	class BaseComp
	{
	public:
		BaseComp(GameObject* gameObject);
		BaseComp() = delete;
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
		virtual void OnColl(GameObject* other) {};

		void SetGameObject(GameObject* object);
		GameObject* GetGameObject() const;

	protected:
		GameObject* m_pGameObject = nullptr;
	};
}

