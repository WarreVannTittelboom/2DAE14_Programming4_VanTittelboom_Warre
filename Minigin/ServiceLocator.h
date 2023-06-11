#pragma once
#include "AudioSystem.h"
#include "Singleton.h"

class ServiceLocator final : public dae::Singleton<ServiceLocator>
{
public:
    static void RegisterSoundSystem(dae::AudioSystem* soundSys);

    static void ReleaseSoundSystem();

    static dae::AudioSystem& GetSoundSystem();

private:
    static dae::AudioSystem* m_pSoundSys;
    static dae::NullAudioSystem m_DefSoundSys;
};