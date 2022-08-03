#pragma once
#include "TronGame.h"
#include "Scene.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TextureComp.h"
#include "InputManager.h"
#include <map>
#include <Command.h>
#include "CollisionComp.h"
#include "Observer.h"
#include "PlayerTank.h"
#include "TronObservers.h"
#include"PlayerBullet.h"
#include "Wall.h"
#include "Button.h"
#include "Teleporter.h"
#include <rapidjson/istreamwrapper.h>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include <fstream>


void dae::TronGame::CreateScenes()
{
	auto& menuScene = dae::SceneManager::GetInstance().CreateScene("Menu");
	auto& coopScene = dae::SceneManager::GetInstance().CreateScene("coop");
	auto& versusScene = dae::SceneManager::GetInstance().CreateScene("versus");
	auto& soloScene = dae::SceneManager::GetInstance().CreateScene("solo");
	

		
	//menu background
	auto background = std::make_shared<dae::GameObject>();
	background->SetPosition(0, 0);
	auto texture = std::make_shared<dae::TextureComp>(background.get(), "../Data/menu.png", 480, 512, true);
	background->AddComponent(texture);
	menuScene.Add(background);
	versusScene.Add(background);

	ReadJsonFile("Level1", menuScene);
	
	//player tank
	/*auto playerTank = std::make_shared<dae::GameObject>();
	playerTank->SetPosition(224, -300);
	auto playerTankComp = std::make_shared<dae::PlayerTank>(playerTank.get(), menuScene,0);
	playerTank->AddComponent(playerTankComp);
	menuScene.Add(playerTank);*/

	auto playerTank2 = std::make_shared<dae::GameObject>();
	playerTank2->SetPosition(224, -300);
	auto playerTankComp2 = std::make_shared<dae::PlayerTank>(playerTank2.get(), versusScene,0);
	playerTank2->AddComponent(playerTankComp2);
	versusScene.Add(playerTank2);

	auto playerTank3 = std::make_shared<dae::GameObject>();
	playerTank3->SetPosition(224, -350);
	auto playerTankComp3 = std::make_shared<dae::PlayerTank>(playerTank3.get(), versusScene,1);
	playerTank3->AddComponent(playerTankComp3);
	versusScene.Add(playerTank3);

	auto teleporter = std::make_shared<dae::GameObject>();
	auto teleporterComp = std::make_shared<dae::Teleporter>(teleporter.get(), 0.f, 0.f, 120.f, 120.f, "../Data/test.png", playerTank2, versusScene);
	teleporter->AddComponent(teleporterComp);
	versusScene.Add(teleporter);

	///////
	// SET TPER IN EVERY LEVEL!!!!!!!!!!!!
	/////

	//auto wall1 = std::make_shared<dae::GameObject>();
	//auto wallComp1 = std::make_shared<dae::Wall>(wall1.get(), 0.f, 0.f, 120.f, 120.f, "../Data/test.png", playerTank, menuScene);
	//wall1->AddComponent(wallComp1);
	//menuScene.Add(wall1);

	//auto wall2 = std::make_shared<dae::GameObject>();
	//auto wallComp2 = std::make_shared<dae::Wall>(wall2.get(), 300.f, 0.f, 120.f, 120.f, "../Data/test.png", playerTank2, menuScene);
	//wall2->AddComponent(wallComp2);
	//menuScene.Add(wall2);
	
	auto wall3 = std::make_shared<dae::GameObject>();
	auto wallComp3 = std::make_shared<dae::Wall>(wall3.get(), 200.f, -80.f, 120.f, 120.f, "../Data/test.png", playerTank2, versusScene);
	wall3->AddComponent(wallComp3);
	versusScene.Add(wall3);

	/*auto wall2 = std::make_shared<dae::GameObject>();
	auto wallComp2 = std::make_shared<dae::Wall>(wall2.get(), 280.f, 0.f, 120.f, 120.f, "../Data/test.png", playerTank,coopScene);
	wall2->AddComponent(wallComp2);
	coopScene.Add(wall2);*/

	auto button1 = std::make_shared<dae::GameObject>();
	button1->SetPosition(40, -300);
	auto button1Comp = std::make_shared<dae::Button>(button1.get(), 100.f, 100.f);
	button1->AddComponent(button1Comp);
	menuScene.Add(button1);
	
	auto button2 = std::make_shared<dae::GameObject>();
	button2->SetPosition(300, -300);
	auto button2Comp = std::make_shared<dae::Button>(button2.get(), 100.f, 100.f);
	button2->AddComponent(button2Comp);
	menuScene.Add(button2);

	auto button3 = std::make_shared<dae::GameObject>();
	button3->SetPosition(170, -150);
	auto button3Comp = std::make_shared<dae::Button>(button3.get(), 100.f, 100.f);
	button3->AddComponent(button3Comp); 
	menuScene.Add(button3);


	coopScene.Add(background);

	soloScene.Add(background);

	
	//versusScene.Add(playerTank);
	
	dae::SceneManager::GetInstance().SetScene("Menu");
}

void dae::TronGame::ReadJsonFile(const std::string& name,Scene& scene)
{
	std::string file{ "../Data/Json/" };
	file += name;
	file += ".json";

	if (std::ifstream input{ file })
	{
		SetConsoleOutputCP(CP_UTF8);
		setvbuf(stdout, nullptr, _IOFBF, 1000);

		rapidjson::IStreamWrapper inputWrapper{ input };
		rapidjson::Document doc;
		doc.ParseStream(inputWrapper);

		const std::string player1Tag = "Player1";
		const std::string player2Tag = "Player2";
		//const std::string enemyTag = "Enemies";
		const std::string wallTag = "Walls";

		std::shared_ptr<GameObject> pTank1;

		for (auto i = doc.Begin(); i != doc.End(); ++i)
		{
			{
				const auto& levelJson = *i;
				const auto& objectJson = levelJson["object"];
				const char* object = objectJson.GetString();
				std::string objectName{ object };

				if (objectName == player1Tag.c_str())
				{
					const auto& playerTransform = levelJson["transform"];
					auto transform = playerTransform.GetArray();
					
					auto playerTank1 = std::make_shared<dae::GameObject>();
					playerTank1->SetPosition(transform[0].GetInt(), transform[1].GetInt());
					auto playerTankComp = std::make_shared<dae::PlayerTank>(playerTank1.get(), scene, 0);
					playerTank1->AddComponent(playerTankComp);
					scene.Add(playerTank1);
					pTank1 = playerTank1;
				}
				if (objectName == player2Tag.c_str())
				{
					const auto& playerTransform = levelJson["transform"];
					auto transform = playerTransform.GetArray();

					auto playerTank2 = std::make_shared<dae::GameObject>();
					playerTank2->SetPosition(transform[0].GetInt(), transform[1].GetInt());
					auto playerTankComp2 = std::make_shared<dae::PlayerTank>(playerTank2.get(), scene, 1);
					playerTank2->AddComponent(playerTankComp2);
					scene.Add(playerTank2);
				}
				//if (objectName == enemyTag.c_str())
				//{
				//	//enemies
				//}
				if (objectName == wallTag.c_str())
				{
					const auto& playerTransform = levelJson["transform"];
					auto transform = playerTransform.GetArray();
					
					auto wall1 = std::make_shared<dae::GameObject>();
					auto wallComp1 = std::make_shared<dae::Wall>(wall1.get(), transform[0].GetFloat(), transform[1].GetFloat(), transform[2].GetFloat(), transform[3].GetFloat(), std::string(transform[4].GetString()), pTank1, scene);
					wall1->AddComponent(wallComp1);
					scene.Add(wall1);
				}

			}
		}
	}
}
