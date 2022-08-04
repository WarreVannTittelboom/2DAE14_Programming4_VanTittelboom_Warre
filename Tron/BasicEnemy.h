#pragma once
#include "BaseComp.h"
#include "GameObject.h"
#include "TronGame.h"
#include "Scene.h"
#include <TextureComp.h>

namespace dae
{
	class BasicEnemy : public dae::BaseComp
	{
	public:
		explicit BasicEnemy(GameObject* gameObject, float x, float y, float w, float h, std::shared_ptr<GameObject> playerTank, Scene& scene);
		~BasicEnemy();
		BasicEnemy(const BasicEnemy& other) = delete;
		BasicEnemy(BasicEnemy&& other) = delete;
		BasicEnemy& operator=(const BasicEnemy& other) = delete;
		BasicEnemy& operator=(BasicEnemy&& other) = delete;

		void Initialize() override;
		void Update() override;
		//void FixedUpdate(float fDT) override;
		//void LateUpdate() override;
		//void Render() const override;
		void OnColl(const GameObject* other) override;
	private:
		float m_EnemySpeed{ 50.f };
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
		std::shared_ptr<GameObject> m_PlayerTank;
	};
}

