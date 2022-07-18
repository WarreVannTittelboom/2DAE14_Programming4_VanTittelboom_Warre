#pragma once
#include "TronGame.h"
#include "Scene.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TextureComp.h"

void dae::TronGame::CreateScenes()
{

	auto& menuScene = dae::SceneManager::GetInstance().CreateScene("Menu");
	auto buttonSolo = std::make_shared<dae::GameObject>();
	buttonSolo->SetPosition(0 , 0);
	auto texture = std::make_shared<dae::TextureComp>(buttonSolo.get(), "../Data/background.jpg",640,480);
	buttonSolo->AddComponent(texture);
	menuScene.Add(buttonSolo);

}
