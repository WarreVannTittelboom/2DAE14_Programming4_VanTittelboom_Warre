#pragma once
#include "BaseComp.h"
#include "Transform.h"
#include "CollisionManager.h"

namespace dae
{
	class CollisionComp : public BaseComp
	{
	public:
		CollisionComp(GameObject* gameObject, float width, float height, bool active = true);
		~CollisionComp() override;
		CollisionComp(const CollisionComp& other) = delete;
		CollisionComp(CollisionComp&& other) noexcept = delete;
		CollisionComp& operator=(const CollisionComp& other) = delete;
		CollisionComp& operator=(CollisionComp&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;

		bool CheckCollision(CollisionComp* pCollider);

		void SetRemoved(bool removed);

		bool IsRemoved() const;
		bool IsActive() const { return m_Active; }
		bool m_Active;
		glm::ivec2 m_Pos{};
		float m_Width;
		float m_Height;
		bool m_Removed;
	};
}



