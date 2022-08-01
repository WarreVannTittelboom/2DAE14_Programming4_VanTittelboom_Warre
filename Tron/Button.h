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
	class Button : public BaseComp
	{
	public:
		explicit Button(GameObject* gameObject, float w, float h);
		~Button();
		Button(const Button& other) = delete;
		Button(Button&& other) = delete;
		Button& operator=(const Button& other) = delete;
		Button& operator=(Button&& other) = delete;

		void Initialize() override;
		float m_PosX{ 0.f };
		float m_PosY{ 0.f };
		float m_Width{ 0.f };
		float m_Height{ 0.f };
		void OnColl(const GameObject* other) override;
	private:
		Scene& m_Scene;
	};
}



