#pragma once
#include "BaseComp.h"
#include "GameObject.h"
#include "TronGame.h"
#include "Scene.h"

namespace dae
{
	class TextureComp;

	class BasicEnemy : public dae::BaseComp
	{
	public:
		explicit BasicEnemy(GameObject* gameObject, float x, float y, float w, float h, Scene& scene);
		~BasicEnemy() = default;
		BasicEnemy(const BasicEnemy& other) = delete;
		BasicEnemy(BasicEnemy&& other) = delete;
		BasicEnemy& operator=(const BasicEnemy& other) = delete;
		BasicEnemy& operator=(BasicEnemy&& other) = delete;

		void Initialize() override;
		void Update() override;
		void OnColl(const GameObject* other) override;

		void ShootCannon(float degreesAngle);
		bool DoDamage();
	private:
		int m_Health{3};
		float m_EnemySpeed{ 40.f };
		float m_ShootCannonCooldown{ 0.f };
		float m_PosX{};
		float m_PosY{};
		float m_Width{};
		float m_Height{};
		bool m_BlockMoveLeft{ false };
		bool m_BlockMoveRight{ false };
		bool m_BlockMoveUp{ false };
		bool m_BlockMoveDown{ false };
		Scene& m_Scene;
		std::shared_ptr<TextureComp> m_enemyHorizontalSprite;
		std::shared_ptr<TextureComp> m_enemyVerticalSprite;

	
	};
}

