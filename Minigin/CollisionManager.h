#pragma once
namespace dae
{
	class CollisionComp;
	
	class CollisionManager
	{
	public:
		CollisionManager() = default;
		~CollisionManager() = default;
		CollisionManager(const CollisionManager& other) = delete;
		CollisionManager(CollisionManager&& other) noexcept = delete;
		CollisionManager& operator=(const CollisionManager& other) = delete;
		CollisionManager& operator=(CollisionManager&& other) noexcept = delete;

		void Update();

		void AddCollider(dae::CollisionComp* pCollider);

	private:
		std::vector<CollisionComp*> m_pColliders{};
	};
}



