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
	class Teleporter : public BaseComp
	{
	public:
		explicit Teleporter(GameObject* gameObject, float x, float y, float w, float h, const std::string& filename, std::shared_ptr<GameObject> playerTank, Scene& scene);

		void Initialize() override;
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



