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
#include "BasicEnemy.h"
#include "RecognizerEnemy.h"


void dae::TronGame::CreateScenes()
{
	auto& menuScene = dae::SceneManager::GetInstance().CreateScene("Menu");
	auto& coopScene1 = dae::SceneManager::GetInstance().CreateScene("coop1");
	auto& versusScene1 = dae::SceneManager::GetInstance().CreateScene("versus1");
	auto& soloScene1 = dae::SceneManager::GetInstance().CreateScene("solo1");
	auto& coopScene2 = dae::SceneManager::GetInstance().CreateScene("coop2");
	auto& versusScene2 = dae::SceneManager::GetInstance().CreateScene("versus2");
	auto& soloScene2 = dae::SceneManager::GetInstance().CreateScene("solo2");
	auto& coopScene3 = dae::SceneManager::GetInstance().CreateScene("coop3");
	auto& versusScene3 = dae::SceneManager::GetInstance().CreateScene("versus3");
	auto& soloScene3 = dae::SceneManager::GetInstance().CreateScene("solo3");
	

		
	//menu background
	auto background = std::make_shared<dae::GameObject>();
	background->SetPosition(0, 0);
	auto texture = std::make_shared<dae::TextureComp>(background.get(), "../Data/menu.png", 480, 512, true);
	background->AddComponent(texture);
	menuScene.Add(background);

	//parsing all levels
	ReadJsonFile("Main", menuScene);
	ReadJsonFile("SingleLevel1", soloScene1);
	ReadJsonFile("SingleLevel2", soloScene2);
	ReadJsonFile("SingleLevel3", soloScene3);
	ReadJsonFile("CoopLevel1", coopScene1);
	ReadJsonFile("CoopleLevel2", coopScene2);
	ReadJsonFile("CoopleLevel3", coopScene3);
	ReadJsonFile("VersusLevel1", versusScene1);
	ReadJsonFile("VersusLevel2", versusScene2);
	ReadJsonFile("VersusLevel3", versusScene3);

	//menu buttons
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
		const std::string enemyTag = "Enemies";
		const std::string specialenemyTag = "RecEnemies";
		const std::string wallTag = "Walls";
		const std::string tpTag = "Teleporter";

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

				if (objectName == tpTag.c_str())
				{
					const auto& tpTransform = levelJson["transform"];
					auto transform = tpTransform.GetArray();
					auto teleporter1 = std::make_shared<dae::GameObject>();
					auto tperComp = std::make_shared<dae::Teleporter>(teleporter1.get(), transform[0].GetFloat(), transform[1].GetFloat(), transform[2].GetFloat(), transform[3].GetFloat(), std::string(transform[4].GetString()), pTank1, scene);
					teleporter1->AddComponent(tperComp);
					scene.Add(teleporter1);
				}
				if (objectName == enemyTag.c_str())
				{
					const auto& playerTransformsJson = levelJson["transform"];
					auto playerTransforms = playerTransformsJson.GetArray();

					for (unsigned int j{}; j < playerTransforms.Size(); j++)
					{
						auto transform = playerTransforms[j].GetArray();

						auto enemy1 = std::make_shared<dae::GameObject>();
						auto enemyComp1 = std::make_shared<dae::BasicEnemy>(enemy1.get(), transform[0].GetFloat(), transform[1].GetFloat(), transform[2].GetFloat(), transform[3].GetFloat(), pTank1, scene);
						enemy1->AddComponent(enemyComp1);
						scene.Add(enemy1);

					}
				}
				if (objectName == specialenemyTag.c_str())
				{
					const auto& playerTransformsJson = levelJson["transform"];
					auto playerTransforms = playerTransformsJson.GetArray();

					for (unsigned int j{}; j < playerTransforms.Size(); j++)
					{
						auto transform = playerTransforms[j].GetArray();

						auto senemy1 = std::make_shared<dae::GameObject>();
						auto senemyComp1 = std::make_shared<dae::RecognizerEnemy>(senemy1.get(), transform[0].GetFloat(), transform[1].GetFloat(), transform[2].GetFloat(), transform[3].GetFloat(), pTank1, scene);
						senemy1->AddComponent(senemyComp1);
						scene.Add(senemy1);

					}
				}
				if (objectName == wallTag.c_str())
				{
					const auto& playerTransformsJson = levelJson["transform"];
					auto playerTransforms = playerTransformsJson.GetArray();

					for (unsigned int j{}; j < playerTransforms.Size(); j++)
					{
						auto transform = playerTransforms[j].GetArray();

						auto wall1 = std::make_shared<dae::GameObject>();
						auto wallComp1 = std::make_shared<dae::Wall>(wall1.get(), transform[0].GetFloat(), transform[1].GetFloat(), transform[2].GetFloat(), transform[3].GetFloat(), std::string(transform[4].GetString()), pTank1, scene);
						wall1->AddComponent(wallComp1);
						scene.Add(wall1);

					}
				}

			}
		}
	}
}
