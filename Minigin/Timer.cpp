#include "MiniginPCH.h"
#include "Timer.h"

void Timer::Set(float time)
{
	m_DeltaTime = time;
	
	m_TotalTime += time;
}
