#pragma once
#include <BaseComp.h>
#include <GameObject.h>
#include <Scene.h>
#include "BaseComp.h"
#include "GameObject.h"
#include "TronGame.h"
#include <TextureComp.h>


namespace dae
{
	class Wall : public BaseComp
	{
	public:
		explicit Wall(GameObject* gameObject,float x,float y,float w,float h,const std::string& filename, std::shared_ptr<GameObject> playerTank, Scene& scene);

		void Initialize() override;
		//void FixedUpdate(float fDT) override;
		//void LateUpdate() override;
		//void Render() const override;
		void OnColl(const GameObject* other) override;
		float m_PosX{ 0.f };
		float m_PosY{ 0.f };
		float m_Width{ 0.f };
		float m_Height{ 0.f };
	private:
		Scene& m_Scene;
		std::string m_FileName{};
		std::shared_ptr<GameObject>  m_PlayerTank;
	};
}



