#pragma once
#include "TronGame.h"
#include "Scene.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TextureComp.h"
#include "InputManager.h"
#include <map>
#include <Command.h>
#include "Scene.h"
#include "CollisionComp.h"
#include "Observer.h"
#include "PlayerTank.h"
#include "TronObservers.h"
#include"PlayerBullet.h"

void dae::TronGame::CreateScenes()
{

	auto& menuScene = dae::SceneManager::GetInstance().CreateScene("Menu");

	//menu background
	auto background = std::make_shared<dae::GameObject>();
	background->SetPosition(0, 0);
	auto texture = std::make_shared<dae::TextureComp>(background.get(), "../Data/menu.png", 480, 512,true);
	background->AddComponent(texture);
	menuScene.Add(background);
	//player tank
	auto playerTank = std::make_shared<dae::GameObject>();
	auto playerTankComp = std::make_shared<dae::PlayerTank>(playerTank.get());
	playerTank->AddComponent(playerTankComp);
	menuScene.Add(playerTank);
	
	
	auto player = std::make_shared<dae::GameObject>();
	player->SetPosition(264, -360);
	auto texture2 = std::make_shared<dae::TextureComp>(player.get(), "../Data/test.png", 120, 120,true);
	player->AddComponent(texture2);
	
	auto playercol = std::make_shared<dae::CollisionComp>(player.get(), 120.f, 120.f, true);
	player->AddComponent(playercol);
	menuScene.AddCollider(playercol);
	CollisionObserver* collideObserver = new CollisionObserver(playerTank);
	player->GetComponent<CollisionComp>()->GetSubject()->AddObserver(collideObserver);
	
	menuScene.Add(player);
}
