#pragma once
#include <Scene.h>
#include "BaseComp.h"
#include "GameObject.h"
#include "TronGame.h"


namespace dae
{
	class TextComp;
	class Font;
	class HUDText : public BaseComp
	{
	public:
		explicit HUDText(GameObject* gameObject,Scene& scene);

		void Initialize() override;
		void Update() override;
	private:
		Scene& m_Scene;
		std::shared_ptr<TextComp> m_LivesCountP1;
		std::shared_ptr<TextComp> m_LivesCountP2;
		std::shared_ptr<TextComp> m_ScoreCount;
	};
}



