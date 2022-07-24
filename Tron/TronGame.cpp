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
	/*auto test = std::make_shared<dae::GameObject>();
	test->SetPosition(0,0);
	auto texture = std::make_shared<dae::TextureComp>(test.get(), "../Data/test.png",200,200);
	test->AddComponent(texture);
	auto player = std::make_shared<dae::GameObject>();
	player->SetPosition(100, 130);
	auto texture2 = std::make_shared<dae::TextureComp>(test.get(), "../Data/test.png", 200, 200);
	player->AddComponent(texture2);
	auto playercol = std::make_shared<dae::CollisionComp>(player.get(), 200.f, 200.f, true);
	player->AddComponent(playercol);
	menuScene.AddCollider(playercol);
	auto testcol = std::make_shared<dae::CollisionComp>(player.get(), 200.f, 200.f, true);
	test->AddComponent(testcol);
	menuScene.AddCollider(testcol);
	CollisionObserver* collideObserver = new CollisionObserver();
	player->GetComponent<CollisionComp>()->GetSubject()->AddObserver(collideObserver);
	std::map<SDL_Scancode, std::shared_ptr<Command>> kInputMap{};
	kInputMap[SDL_SCANCODE_A] = std::make_shared<TestCommand>(player.get());
	dae::InputManager::GetInstance().AddCommand(kInputMap, 0);
	std::map<controlButton, std::shared_ptr<Command>> cInputMap{};
	cInputMap[controlButton::DpadLeft] = std::make_shared<TestCommand>(player.get());
	InputManager::GetInstance().AddCommand(cInputMap, 0);
	menuScene.Add(test);
	menuScene.Add(player);*/
}
