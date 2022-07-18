#pragma once
#include "Singleton.h"

class Timer final : public dae::Singleton<Timer>
{
public:
	void Set(float time);
	float GetDeltaTime() const { return m_DeltaTime; }
	float GetTotalTime() const { return m_TotalTime; }
private:
	float m_DeltaTime{};
	float m_TotalTime{};
};

