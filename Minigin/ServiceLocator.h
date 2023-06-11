#pragma once
#include "AudioSystem.h"
#include "Singleton.h"

class ServiceLocator final : public dae::Singleton<ServiceLocator>
{
public:
    static void RegisterSoundSystem(dae::AudioSystem* soundSys)
    {
        m_pSoundSys = soundSys == nullptr ? &m_DefSoundSys : soundSys;
    }

    static void ReleaseSoundSystem()
    {
        delete m_pSoundSys;
        m_pSoundSys = nullptr;
    }

    static dae::AudioSystem& GetSoundSystem() { return *m_pSoundSys; }

private:
    static dae::AudioSystem* m_pSoundSys;
    static dae::NullAudioSystem m_DefSoundSys;
};

dae::NullAudioSystem ServiceLocator::m_DefSoundSys;
dae::AudioSystem* ServiceLocator::m_pSoundSys = &m_DefSoundSys;