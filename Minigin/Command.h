#pragma once
#include "GameObject.h"
#include "BaseComp.h"

class Command
{
public:
	explicit Command(dae::GameObject* object) :m_pGameObject(object){};
	virtual ~Command() = default;
	
	virtual void Execute() = 0;
	
	virtual void Release() = 0;
protected:
	
	dae::GameObject* GetObj() const { return m_pGameObject; };
private:
	
	dae::GameObject* m_pGameObject = nullptr;
};

class TestCommand : public Command
{
public:
	TestCommand(dae::GameObject* go)
		:Command(go)
	{
	};
	void Execute() override { std::cout << "Test begin\n"; }
	void Release() override { std::cout << "Test command end\n"; }

	
};

