#include "MiniginPCH.h"
#include "Subject.h"


dae::Subject::~Subject() 
{
	for (auto& observer : m_pObservers)
	{ 
		delete observer; 
		observer = nullptr;
	}
}
void dae::Subject::Notify(const dae::GameObject* e, Event event)
{
	for (size_t i = 0; i < m_pObservers.size(); ++i)
	{
		m_pObservers[i]->OnNotify(e, event);
	}
}

void dae::Subject::AddObserver(Observer* observer)
{
	m_pObservers.push_back(observer);
}

void dae::Subject::RemoveObserver(const Observer* observer)
{
	std::erase(m_pObservers, observer);
}
