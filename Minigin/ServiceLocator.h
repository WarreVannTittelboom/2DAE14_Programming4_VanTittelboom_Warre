#pragma once
#include "AudioSystem.h"
#include "Singleton.h"

class ServiceLocator final : public dae::Singleton<ServiceLocator>
{
public:
	static void RegisterSoundSystem(dae::AudioSystemAbs* soundSys)
	{
		m_pSoundSys = soundSys == nullptr ? &m_DefSoundSys : soundSys;
	}

	static void ReleaseSoundSystem()
	{
		delete m_pSoundSys;
		m_pSoundSys = nullptr;
	}


	static dae::AudioSystemAbs& GetSoundSystem() { return *m_pSoundSys; }

private:
	static dae::AudioSystemAbs* m_pSoundSys;
	static dae::NullAudioSystem m_DefSoundSys;
};


dae::NullAudioSystem ServiceLocator::m_DefSoundSys;
dae::AudioSystemAbs* ServiceLocator::m_pSoundSys = &m_DefSoundSys;
