#pragma once
#include "BaseComp.h"
#include "GameObject.h"
#include "TronGame.h"
#include "Scene.h"
#include <TextureComp.h>

namespace dae
{
	class PlayerTank : public dae::BaseComp
	{
	public:
		explicit PlayerTank(dae::GameObject* gameObject);
		~PlayerTank();
		PlayerTank(const PlayerTank& other) = delete;
		PlayerTank(PlayerTank&& other) = delete;
		PlayerTank& operator=(const PlayerTank& other) = delete;
		PlayerTank& operator=(PlayerTank&& other) = delete;

		void Initialize() override;
		void Update() override;
		//void FixedUpdate(float fDT) override;
		//void LateUpdate() override;
		void Render() const override;
		void OnColl(const GameObject* other) override;
	
		void SetMoveLeft(bool moveLeft) { m_MoveLeft = moveLeft; }
		void SetMoveRight(bool moveRight) { m_MoveRight = moveRight; }
		void SetMoveUp(bool moveUp) { m_MoveUp = moveUp; }
		void SetMoveDown(bool moveDown) { m_MoveDown = moveDown; }
		
		void SetDoShoot(bool doShoot) { m_DoShoot = doShoot; }
		
		void SetMoveCannonLeft(bool moveCannonLeft) { m_MoveCannonLeft = moveCannonLeft; }
		void SetMoveCannonRight(bool moveCannonRight) { m_MoveCannonRight = moveCannonRight; }
	
	private:
		void InitTurretSprites();
		void Test();
		float m_PlayerSpeed{50.f};
		int m_TurretMoveIter{0};
		float m_MoveCannonCooldown{ 0.f };
		float m_ShootCannonCooldown{ 0.f };
		bool m_MoveLeft{ false };
		bool m_MoveRight{ false };
		bool m_MoveUp{ false };
		bool m_MoveDown{ false };
		
		bool m_BlockMoveLeft{ false };
		bool m_BlockMoveRight{ false };
		bool m_BlockMoveUp{ false };
		bool m_BlockMoveDown{ false };


		bool m_DoShoot{ false };

		bool m_MoveCannonLeft{ false };
		bool m_MoveCannonRight{ false };

		Scene& m_Scene;
		std::shared_ptr<TextureComp> m_playerHorizontalSprite;
		std::shared_ptr<TextureComp> m_playerVerticalSprite;
		std::vector <std::shared_ptr<TextureComp>> m_playerCannonSprites;
	};
}

