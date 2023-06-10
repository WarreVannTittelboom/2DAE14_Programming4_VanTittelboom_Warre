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
#include <Font.h>
#include <TextComp.h>
#include "HUDText.h"
#include "EnemyBullet.h"



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
	dae::SceneManager::GetInstance().CreateScene("gameoverscene");



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
	ReadJsonFile("CoopLevel2", coopScene2);
	ReadJsonFile("CoopLevel3", coopScene3);
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

	//game over text 
	auto text = std::make_shared<dae::GameObject>();
	auto font = std::make_shared<dae::Font>("../Data/Lingua.otf", 40);
	auto textcomp = std::make_shared<dae::TextComp>(text.get(), "temp", font);
	textcomp->SetPos(135, 270);
	text->AddComponent(textcomp);
	dae::SceneManager::GetInstance().GetScene("gameoverscene").Add(text);

	dae::SceneManager::GetInstance().SetScene("Menu");
}

void dae::TronGame::ReadJsonFile(const std::string& name, Scene& scene)
{
	std::string file{ "../Data/Json/" };
	file += name;
	file += ".json";
	scene.m_FileName = name;
	if (std::ifstream input{ file })
	{
		SetConsoleOutputCP(CP_UTF8);
		setvbuf(stdout, nullptr, _IOFBF, 1000);

		rapidjson::IStreamWrapper inputWrapper{ input };
		rapidjson::Document doc;
		doc.ParseStream(inputWrapper);

		const std::string player0Tag = "Player0";
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

				if (objectName == player0Tag.c_str())
				{
					const auto& playerTransform = levelJson["transform"];
					auto transform = playerTransform.GetArray();

					auto playerTank0 = std::make_shared<dae::GameObject>();
					playerTank0->SetPosition(transform[0].GetInt(), transform[1].GetInt());
					auto playerTankComp0 = std::make_shared<dae::PlayerTank>(playerTank0.get(), scene, 0);
					playerTank0->AddComponent(playerTankComp0);
					scene.Add(playerTank0);
					pTank1 = playerTank0;
				}
				if (objectName == player1Tag.c_str())
				{
					const auto& playerTransform = levelJson["transform"];
					auto transform = playerTransform.GetArray();

					auto playerTank1 = std::make_shared<dae::GameObject>();
					playerTank1->SetPosition(transform[0].GetInt(), transform[1].GetInt());
					auto playerTankComp1 = std::make_shared<dae::PlayerTank>(playerTank1.get(), scene, 1);
					playerTank1->AddComponent(playerTankComp1);
					scene.Add(playerTank1);
					pTank1 = playerTank1;
				}
				if (objectName == player2Tag.c_str())
				{
					const auto& playerTransform = levelJson["transform"];
					auto transform = playerTransform.GetArray();

					auto playerTank2 = std::make_shared<dae::GameObject>();
					playerTank2->SetPosition(transform[0].GetInt(), transform[1].GetInt());
					auto playerTankComp2 = std::make_shared<dae::PlayerTank>(playerTank2.get(), scene, 2);
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
						auto enemyComp1 = std::make_shared<dae::BasicEnemy>(enemy1.get(), transform[0].GetFloat(), transform[1].GetFloat(), transform[2].GetFloat(), transform[3].GetFloat(), scene);
						enemy1->AddComponent(enemyComp1);
						scene.Add(enemy1);
						scene.m_TotalEnemyCount+= 1;
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
						auto senemyComp1 = std::make_shared<dae::RecognizerEnemy>(senemy1.get(), transform[0].GetFloat(), transform[1].GetFloat(), transform[2].GetFloat(), transform[3].GetFloat(), scene);
						senemy1->AddComponent(senemyComp1);
						scene.Add(senemy1);
						scene.m_TotalEnemyCount += 1;
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
						auto wallComp1 = std::make_shared<dae::Wall>(wall1.get(), transform[0].GetFloat(), transform[1].GetFloat(), transform[2].GetFloat(), transform[3].GetFloat(), std::string(transform[4].GetString()),scene);
						wall1->AddComponent(wallComp1);
						scene.Add(wall1);

					}
				}

			}
		}

	}
	if (name != "Main")
	{
		auto textObj = std::make_shared<dae::GameObject>();
		auto textObjComp = std::make_shared<dae::HUDText>(textObj.get(), scene);
		textObj->AddComponent(textObjComp);
		scene.Add(textObj);
	}
}


void dae::TronGame::ReadJsonFileReset(const std::string& name, dae::Scene& scene)
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

		const std::string player0Tag = "Player0";
		const std::string player1Tag = "Player1";
		const std::string player2Tag = "Player2";
		const std::string enemyTag = "Enemies";
		const std::string specialenemyTag = "RecEnemies";
		int PosXP1 = 0;
		int PosYP1 = 0;
		int PosXP2 = 0;
		int PosYP2 = 0;


		for (auto i = doc.Begin(); i != doc.End(); ++i)
		{
			{
				const auto& levelJson = *i;
				const auto& objectJson = levelJson["object"];
				const char* object = objectJson.GetString();
				std::string objectName{ object };

				if (objectName == player0Tag.c_str())
				{
					const auto& playerTransform = levelJson["transform"];
					auto transform = playerTransform.GetArray();
					
					PosXP1 = transform[0].GetInt();
					PosYP1 = transform[1].GetInt();
				}
				if (objectName == player1Tag.c_str())
				{
					const auto& playerTransform = levelJson["transform"];
					auto transform = playerTransform.GetArray();

					PosXP1 = transform[0].GetInt();
					PosYP1 = transform[1].GetInt();
				}
				if (objectName == player2Tag.c_str())
				{
					const auto& playerTransform = levelJson["transform"];
					auto transform = playerTransform.GetArray();

					PosXP2 = transform[0].GetInt();
					PosYP2 = transform[1].GetInt();
				}

				if (objectName == enemyTag.c_str())
				{
					const auto& playerTransformsJson = levelJson["transform"];
					auto playerTransforms = playerTransformsJson.GetArray();

					for (unsigned int j{}; j < playerTransforms.Size(); j++)
					{
						auto transform = playerTransforms[j].GetArray();

						auto enemy1 = std::make_shared<dae::GameObject>();
						auto enemyComp1 = std::make_shared<dae::BasicEnemy>(enemy1.get(), transform[0].GetFloat(), transform[1].GetFloat(), transform[2].GetFloat(), transform[3].GetFloat(), scene);
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
						auto senemyComp1 = std::make_shared<dae::RecognizerEnemy>(senemy1.get(), transform[0].GetFloat(), transform[1].GetFloat(), transform[2].GetFloat(), transform[3].GetFloat(), scene);
						senemy1->AddComponent(senemyComp1);
						scene.Add(senemy1);
					}
				}

			}
		}
		auto players = dae::SceneManager::GetInstance().GetActiveScene().FindObjectsOfType<PlayerTank>();
		bool playertwo = false;
		for (auto player : players)
		{
			if (playertwo)
			{

				if (m_LivesP2 >= 0)
				{
					player->GetGameObject()->SetPosition(PosXP2, PosYP2);
				}
				

			}

			else
			{

				if (m_LivesP1 >= 0)
				{
					player->GetGameObject()->SetPosition(PosXP1, PosYP1);
				}
				

			}
			playertwo = true;
		}
	}
}

void dae::TronGame::ResetLevelForNext()
{
	auto players = dae::SceneManager::GetInstance().GetActiveScene().FindObjectsOfType<PlayerTank>();
	bool playertwo = false;
	for (auto player : players)
	{
		if (playertwo)
		{
			
			
				player->GetGameObject()->SetPosition(800, 800);
			
		}
		
		else
			{
				
				
				
					player->GetGameObject()->SetPosition(800, 800);
				
			}
		playertwo= true;
	}
	auto enemies = dae::SceneManager::GetInstance().GetActiveScene().FindObjectsOfType<BasicEnemy>();
	for (auto enemy : enemies)
	{
		enemy->GetGameObject()->SetPosition(-1000, -1000);
	}
	auto senemies = dae::SceneManager::GetInstance().GetActiveScene().FindObjectsOfType<RecognizerEnemy>();
	for (auto senemy : senemies)
	{
		senemy->GetGameObject()->SetPosition(-1000, -1000);
	}

	auto bulllets = dae::SceneManager::GetInstance().GetActiveScene().FindObjectsOfType<PlayerBullet>();
	for (auto bullet : bulllets)
	{
		bullet->GetGameObject()->SetPosition(1000, 1000);
	}
	auto enemyBullets = dae::SceneManager::GetInstance().GetActiveScene().FindObjectsOfType<EnemyBullet>();
	for (auto enemybullet : enemyBullets)
	{
		enemybullet->GetGameObject()->SetPosition(-1000, 1000);
	}

	ReadJsonFileReset(dae::SceneManager::GetInstance().GetActiveScene().m_FileName, dae::SceneManager::GetInstance().GetActiveScene());
}

void dae::TronGame::LoadNextScene()
{
	SDL_Event event;
	SDL_zero(event);

	event.type = SDL_KEYDOWN;
	event.key.keysym.scancode = SDL_SCANCODE_N;

	SDL_PushEvent(&event);
	
	m_DeadP2 = false;
	m_DeadP1 = false;
}

void dae::TronGame::ResetGame()
{
	dae::SceneManager::GetInstance().SetScene("Menu");
	m_Score = 0;
	m_LivesP1 = 3;
	m_LivesP2 = 3;
	m_DeadP1 = false;
	m_DeadP2 = false;
	auto players = dae::SceneManager::GetInstance().GetActiveScene().FindObjectsOfType<PlayerTank>();
	bool playertwo = false;
	for (auto player : players)
	{
		if (playertwo)
		{
			
			
				player->GetGameObject()->SetPosition(224, -350);
			
		}

		else
		{
			
			
				player->GetGameObject()->SetPosition(224, -310);
			
		}
		playertwo = true;
	}
}
