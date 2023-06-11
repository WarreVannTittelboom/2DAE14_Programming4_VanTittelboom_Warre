#include "MiniginPCH.h"
#include "ServiceLocator.h"

dae::NullAudioSystem ServiceLocator::m_DefSoundSys;
dae::AudioSystem* ServiceLocator::m_pSoundSys = &m_DefSoundSys;

void ServiceLocator::RegisterSoundSystem(dae::AudioSystem* soundSys)
{
	m_pSoundSys = soundSys == nullptr ? &m_DefSoundSys : soundSys;
}

void ServiceLocator::ReleaseSoundSystem()
{
	delete m_pSoundSys;
	m_pSoundSys = nullptr;
}

dae::AudioSystem& ServiceLocator::GetSoundSystem()
{
	return *m_pSoundSys;
}
