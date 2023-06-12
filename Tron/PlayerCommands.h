#include "BaseComp.h"
#include "GameObject.h"
#include <Command.h>
#include "PlayerTank.h"
#include <SceneManager.h>
#include "TronGame.h"
#include <Scene.h>

class MovePlayer : public Command
{
public:
	MovePlayer(dae::GameObject* go, dae::PlayerTank::Direction dir)
		:Command(go)
	{
		m_Dir = dir;
	};
	void Execute() override { if (!GetObj()->IsMarkedForDestroy() && GetObj() != nullptr) { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveDir(true, m_Dir); } }
	void Release() override { if (!GetObj()->IsMarkedForDestroy() && GetObj() != nullptr) { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveDir(false, m_Dir); } }
	dae::PlayerTank::Direction m_Dir;
};

class DoShoot : public Command
{
public:
	DoShoot(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override { if (!GetObj()->IsMarkedForDestroy() && GetObj() != nullptr) { GetObj()->GetComponent<dae::PlayerTank>()->SetDoShoot(true); } }
	void Release() override { if (!GetObj()->IsMarkedForDestroy() && GetObj() != nullptr) { GetObj()->GetComponent<dae::PlayerTank>()->SetDoShoot(false); } }


};


class CannonLeft : public Command
{
public:
	CannonLeft(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override { if (!GetObj()->IsMarkedForDestroy() && GetObj() != nullptr) { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveCannonLeft(true); } }
	void Release() override { if (!GetObj()->IsMarkedForDestroy() && GetObj() != nullptr) { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveCannonLeft(false); } }


};


class CannonRight : public Command
{
public:
	CannonRight(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override { if (!GetObj()->IsMarkedForDestroy() && GetObj() != nullptr) { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveCannonRight(true); } }
	void Release() override { if (!GetObj()->IsMarkedForDestroy() && GetObj() != nullptr) { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveCannonRight(false); } }


};

class NextScene : public Command
{
public:
	NextScene(dae::GameObject* go)
		:Command(go)
	{	
	};
	void Execute() override 
	{ 
		
	
	}
	void Release() override 
	{ 
		{
			dae::TronGame::GetInstance().ResetLevelForNext();

			if (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "coop1")

			{
				dae::SceneManager::GetInstance().SetScene("coop2");
			}
			else if (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "coop2")
			{
				dae::SceneManager::GetInstance().SetScene("coop3");
			}
			else if (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "coop3")
			{
				dae::SceneManager::GetInstance().SetScene("coop1");
			}
			else if (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "solo1")
			{
				dae::SceneManager::GetInstance().SetScene("solo2");
			}
			else if (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "solo2")
			{
				dae::SceneManager::GetInstance().SetScene("solo3");
			}
			else if (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "solo3")
			{
				dae::SceneManager::GetInstance().SetScene("solo1");
			}
			else if (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "versus1")
			{
				dae::SceneManager::GetInstance().SetScene("versus2");
			}
			else if (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "versus2")
			{
				dae::SceneManager::GetInstance().SetScene("versus3");
			}
			else if (dae::SceneManager::GetInstance().GetActiveScene().GetName() == "versus3")
			{
				dae::SceneManager::GetInstance().SetScene("versus1");
			}
		}
	}
};

class ReturnToMenu: public Command
{
public:
	ReturnToMenu(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override
	{
		
	}
	void Release() override 
	{ 
			dae::TronGame::GetInstance().ResetLevelForNext();
			dae::TronGame::GetInstance().ResetGame();
	}


};


class ToggleMute : public Command
{
public:
	ToggleMute(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override
	{
		
	}
	void Release() override 
	{ 
			dae::TronGame::GetInstance().DoMute();
	}


};

