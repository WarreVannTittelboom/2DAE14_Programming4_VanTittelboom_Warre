#include "BaseComp.h"
#include "GameObject.h"
#include <Command.h>
#include "PlayerTank.h"

class MoveLeft : public Command
{
public:
	MoveLeft(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveLeft(true); }
	void Release() override { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveLeft(false); }


};

class MoveRight : public Command
{
public:
	MoveRight(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveRight(true); }
	void Release() override { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveRight(false); }


};

class MoveUp : public Command
{
public:
	MoveUp(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveUp(true); }
	void Release() override { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveUp(false); }



};

class MoveDown : public Command
{
public:
	MoveDown(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveDown(true); }
	void Release() override { GetObj()->GetComponent<dae::PlayerTank>()->SetMoveDown(false); }

};

class DoShoot : public Command
{
public:
	DoShoot(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override { std::cout << "Test begin\n"; }
	void Release() override { std::cout << "Test command end\n"; }


};


class CannonLeft : public Command
{
public:
	CannonLeft(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override { std::cout << "Test begin\n"; }
	void Release() override { std::cout << "Test command end\n"; }


};


class CannonRight : public Command
{
public:
	CannonRight(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override { std::cout << "Test begin\n"; }
	void Release() override { std::cout << "Test command end\n"; }


};

