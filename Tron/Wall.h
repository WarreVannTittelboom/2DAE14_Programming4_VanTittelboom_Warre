#pragma once
#include "Scene.h"
#include "BaseComp.h"
#include "GameObject.h"
#include "TronGame.h"


namespace dae
{
	class TextureComp;

	class Wall : public BaseComp
	{
	public:
		explicit Wall(GameObject* gameObject,float x,float y,float w,float h,const std::string& filename, Scene& scene);

		void Initialize() override;
		float m_PosX{ 0.f };
		float m_PosY{ 0.f };
		float m_Width{ 0.f };
		float m_Height{ 0.f };
	private:
		Scene& m_Scene;
		std::string m_FileName{};
	};
}



