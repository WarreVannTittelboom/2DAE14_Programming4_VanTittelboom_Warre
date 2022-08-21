#pragma once
#include "BaseComp.h"
#include "GameObject.h"
#include "TronGame.h"
#include "Scene.h"
#include <TextureComp.h>

namespace dae
{
	class RecognizerEnemy : public dae::BaseComp
	{
	public:
		explicit RecognizerEnemy(GameObject* gameObject, float x, float y, float w, float h, std::shared_ptr<GameObject> playerTank, Scene& scene);
		~RecognizerEnemy();
		RecognizerEnemy(const RecognizerEnemy& other) = delete;
		RecognizerEnemy(RecognizerEnemy&& other) = delete;
		RecognizerEnemy& operator=(const RecognizerEnemy& other) = delete;
		RecognizerEnemy& operator=(RecognizerEnemy&& other) = delete;

		void Initialize() override;
		void Update() override;
		void OnColl(const GameObject* other) override;
		
		bool DoDamage();
	private:
		int m_Health{3};
		float m_EnemySpeed{ 80.f };
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

