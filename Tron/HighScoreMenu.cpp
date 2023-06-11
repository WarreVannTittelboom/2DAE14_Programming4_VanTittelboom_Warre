#include "HighScoreMenu.h"
#include "TextComp.h"
#include "Font.h"
#include <algorithm>

dae::HighScoreMenu::HighScoreMenu(GameObject* gameObject, Scene& scene)
	:BaseComp(gameObject)
	, m_Scene(scene)
{
}

void dae::HighScoreMenu::Initialize()
{
	auto hfont = std::make_shared<dae::Font>("../Data/Lingua.otf", 15);
	auto title = std::make_shared<dae::TextComp>(GetGameObject(), "HighScores: ", hfont);
	title->SetPos(335.f, 20.f);
	GetGameObject()->AddComponent(title);
	for (int i = 0; m_HighScoreCount > i; ++i)
	{
		auto font = std::make_shared<dae::Font>("../Data/Lingua.otf", 15);
		auto highScore = std::make_shared<dae::TextComp>(GetGameObject(), "HighScore: " + std::to_string(i), font);
		highScore->SetPos(335.f, 40.f + (i * 20));
		m_HighScores.push_back(highScore);
		GetGameObject()->AddComponent(m_HighScores[i]);
	}
}

void dae::HighScoreMenu::LoadScores()
{
	auto scores = dae::TronGame::GetInstance().ReadScoresFromFile();
	scores.push_back(dae::TronGame::GetInstance().m_Score);
	std::sort(scores.rbegin(), scores.rend());
	if (scores.size() > 10) 
	{
		scores.resize(10);
	}
	dae::TronGame::GetInstance().SaveScoresToFile(scores);
	for (int i = 0; m_HighScoreCount > i; ++i)
	{
		m_HighScores[i]->SetText( std::to_string(i+1) + ". " + std::to_string(scores[i]));
	}
}
