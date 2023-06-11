#pragma once
#include <BaseComp.h>
#include <GameObject.h>
#include <Scene.h>
#include "BaseComp.h"
#include "GameObject.h"
#include "TronGame.h"


namespace dae
{
	class TextComp;
	class Font;
	class HighScoreMenu : public BaseComp
	{
	public:
		explicit HighScoreMenu(GameObject* gameObject, Scene& scene);

		void Initialize() override;
		void LoadScores();
	private:
		Scene& m_Scene;
		std::vector <std::shared_ptr<TextComp>> m_HighScores;
		std::shared_ptr<TextComp> m_Title;
		int m_HighScoreCount{ 10 };
	};
}



