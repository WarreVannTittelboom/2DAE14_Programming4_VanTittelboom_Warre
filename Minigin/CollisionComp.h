#pragma once
#include "BaseComp.h"
#include "Transform.h"

namespace dae
{
	class CollisionComp : public BaseComp
	{
	public:
		CollisionComp(GameObject* gameObject, float width, float height, bool active = true);
		~CollisionComp() override = default;
		CollisionComp(const CollisionComp& other) = delete;
		CollisionComp(CollisionComp&& other) noexcept = delete;
		CollisionComp& operator=(const CollisionComp& other) = delete;
		CollisionComp& operator=(CollisionComp&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;

		bool CheckCollision(CollisionComp* pCollider);

		bool m_Active;
		glm::ivec2 m_Pos{};
		float m_Width;
		float m_Height;
	private:
		
	};
}



