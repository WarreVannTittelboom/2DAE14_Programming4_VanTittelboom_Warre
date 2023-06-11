#pragma once
#include <BaseComp.h>
#include <GameObject.h>
#include <Scene.h>

namespace dae
{
	class EnemyBullet : public BaseComp
	{
	public:
		explicit EnemyBullet(GameObject* gameObject, float x, float y, float cosx, float siny, Scene& scene);
		~EnemyBullet();
		EnemyBullet(const EnemyBullet& other) = delete;
		EnemyBullet(EnemyBullet&& other) = delete;
		EnemyBullet& operator=(const EnemyBullet& other) = delete;
		EnemyBullet& operator=(EnemyBullet&& other) = delete;

		void Initialize() override;
		void Update() override;
		void OnColl(const GameObject* other) override;
		bool m_Active = true;
	private:
		float m_BulletSpeed{ 80.f };
		float m_StartPosX{ 0.f };
		float m_StartPosY{ 0.f };
		float m_CosX{ 0.f };
		float m_SinY{ 0.f };
		Scene& m_Scene;
	};
}

