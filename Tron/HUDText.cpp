#include "HUDText.h"
#include "TextComp.h"
#include "Font.h"


dae::HUDText::HUDText(GameObject* gameObject, Scene& scene)
	:BaseComp(gameObject)
	, m_Scene(scene)
{
}

void dae::HUDText::Initialize()
{
	auto font = std::make_shared<dae::Font>("../Data/Lingua.otf", 20);
	m_LivesCountP1 = std::make_shared<dae::TextComp>(GetGameObject(), "Lives: " + std::to_string(dae::TronGame::GetInstance().m_LivesP1), font);
	m_LivesCountP1->SetPos(365, 20);
	GetGameObject()->AddComponent(m_LivesCountP1);
	if (m_Scene.m_FileName != "SingleLevel1" && m_Scene.m_FileName != "SingleLevel2" && m_Scene.m_FileName != "SingleLevel3")
	{
		m_LivesCountP2 = std::make_shared<dae::TextComp>(GetGameObject(), "Lives: " + std::to_string(dae::TronGame::GetInstance().m_LivesP2), font);
		m_LivesCountP2->SetPos(365, 40);
		GetGameObject()->AddComponent(m_LivesCountP2);
	}
	m_ScoreCount = std::make_shared<dae::TextComp>(GetGameObject(), "Lives: " + std::to_string(dae::TronGame::GetInstance().m_Score), font);
	m_ScoreCount->SetPos(385, 470);
	GetGameObject()->AddComponent(m_ScoreCount);
}

void dae::HUDText::Update()
{
	m_LivesCountP1->SetText("Lives P1: " + std::to_string(dae::TronGame::GetInstance().m_LivesP1));
	if (m_Scene.m_FileName != "SingleLevel1" && m_Scene.m_FileName != "SingleLevel2" && m_Scene.m_FileName != "SingleLevel3")
	{
		m_LivesCountP2->SetText("Lives P2: " + std::to_string(dae::TronGame::GetInstance().m_LivesP2));
	}
	m_ScoreCount->SetText("Score: " + std::to_string(dae::TronGame::GetInstance().m_Score));
}
