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

		void DoWander();
		void DoMoveToPlayer();
		void DoMoveToLastPlayerPos();
		void UpdateMovement();
		bool HasReachedLastPlayerPos();
		bool CheckPlayerInRange();
		void RandomizeDirection();
		void ColEdgeCases();

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
		float m_TargetPosX{ 0.f };
		float m_TargetPosY{ 0.f };
		float m_PlayerTargetPosX{ 0.f };
		float m_PlayerTargetPosY{ 0.f };
		float m_LastPlayerPosX{ 0.f };
		float m_LastPlayerPosY{ 0.f };
		bool m_Wander{ true };
		int m_Direction{ 0 };
		float m_ChangeDirTimer{ 0.f };
		float m_ChangeDirMaxTime{ 10.f };
		float m_StuckTimer{ 0.f };
		float m_MaxStuckTimer{ 5.f };
		Scene& m_Scene;
		std::shared_ptr<TextureComp> m_enemyHorizontalSprite;
		std::shared_ptr<TextureComp> m_enemyVerticalSprite;
		enum RecognizerEnemyState
		{
			Wander,
			MoveToPlayer,
			MoveToLastPlayerPos
		};

		RecognizerEnemyState m_CurrentState{ RecognizerEnemyState::Wander };

	
	};
}

