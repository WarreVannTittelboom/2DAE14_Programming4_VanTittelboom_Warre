#include "MiniginPCH.h"
#include "AudioClip.h"

AudioClip::AudioClip(const std::string& path, int loops, int volume)
	:m_FilePath{ path }
	, m_Volume{ volume }
	, m_Loops{ loops }
{
}

AudioClip::~AudioClip()
{
	Mix_FreeChunk(m_pChunk);
	m_pChunk = nullptr;
	std::cout << "Destroyed AudioClip\n" << std::endl;
}

bool AudioClip::operator==(const AudioClip& ac) const
{
	return ac.m_Loops == m_Loops && ac.m_Volume == m_Volume && ac.m_FilePath == m_FilePath;
}

bool AudioClip::LoadWav()
{
	m_pChunk = Mix_LoadWAV(m_FilePath.c_str());
	if (m_pChunk) { SetVolume(m_Volume); return true; }
	std::cout << "Mixer error loading Wav file!\n";
	return false;

}

void AudioClip::SetVolume(const int volume)
{
	if (m_pChunk)
	{
		m_Volume = Mix_VolumeChunk(m_pChunk, volume);
		std::cout << "Set volume to: " + std::to_string(m_Volume) << "\n";
	}
}

void AudioClip::Play()
{
	m_Channel = Mix_PlayChannel(-1, m_pChunk, m_Loops);
	if (m_Channel == -1)
	{
		std::cout << "Mixer error playing AudioClip\n";
	}
}

void AudioClip::Pause() const
{
	if (m_Channel != -1)
	{
		Mix_Pause(m_Channel);
	}
}

void AudioClip::Resume() const
{
	if (m_Channel != -1)
	{
		Mix_Resume(m_Channel);
	}
}

bool AudioClip::IsPlaying() const
{
	return Mix_Playing(m_Channel) == 1;
}