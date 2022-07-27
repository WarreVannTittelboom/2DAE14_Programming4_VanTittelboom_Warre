#pragma once
#include <BaseComp.h>
#include <GameObject.h>
#include <Scene.h>

namespace dae
{ 
class PlayerBullet : public BaseComp
{
public:
	explicit PlayerBullet(GameObject* gameObject,float x,float y, float cosx, float siny);
	~PlayerBullet();
	PlayerBullet(const PlayerBullet& other) = delete;
	PlayerBullet(PlayerBullet&& other) = delete;
	PlayerBullet& operator=(const PlayerBullet& other) = delete;
	PlayerBullet& operator=(PlayerBullet&& other) = delete;

	void Initialize() override;
	void Update() override;
	//void FixedUpdate(float fDT) override;
	//void LateUpdate() override;
	void Render() const override;
	void OnColl(const GameObject* other) override;
private:
	float m_BulletSpeed{ 80.f };
	int m_BounceCount{ 3 };
	float m_StartPosX{ 0.f };
	float m_StartPosY{ 0.f };
	float m_CosX{ 0.f };
	float m_SinY{ 0.f };
	Scene& m_Scene;
};
}

