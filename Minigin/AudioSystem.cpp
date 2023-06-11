#include "MiniginPCH.h"
#include "AudioSystem.h"


class dae::AudioSystem::AudioSystemImpl final
{
public:
	AudioSystemImpl();
	~AudioSystemImpl();
	AudioSystemImpl(const AudioSystemImpl& other) = delete;
	AudioSystemImpl(AudioSystemImpl&& other) noexcept = delete;
	AudioSystemImpl& operator=(const AudioSystemImpl& other) = delete;
	AudioSystemImpl& operator=(AudioSystemImpl&& other) noexcept = delete;

	void Enqueue(const std::string& filename, int loops = 0, int volume = 50);
	void CheckQueue();
	void StopQueue() { m_IsActive = false; };
	void Mute(bool isMuted);

private:
	void PlaySound(AudioClip* clip);
	bool LoadSound(AudioClip* clip);

	std::jthread m_thread;
	std::mutex m_QueueMutex;
	std::queue<AudioClip*> m_pAudioQueue{};
	std::mutex m_ClipMutex;
	std::vector<AudioClip*> m_Clips{};
	bool m_IsActive = true;
};

dae::AudioSystem::AudioSystemImpl::AudioSystemImpl()
{
	Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048);
	m_thread = std::jthread(&AudioSystemImpl::CheckQueue, this);
}


dae::AudioSystem::AudioSystemImpl::~AudioSystemImpl()
{
	m_IsActive = false;
	if (m_thread.joinable())
	{
		m_thread.join();
	}

	{
		std::lock_guard<std::mutex> lock(m_QueueMutex);
		while (!m_pAudioQueue.empty())
		{
			delete m_pAudioQueue.front();
			m_pAudioQueue.pop();
		}
	}

	{
		std::lock_guard<std::mutex> lock(m_ClipMutex);
		for (AudioClip* clip : m_Clips)
		{
			delete clip;
		}
		m_Clips.clear();
	}
	Mix_CloseAudio();
}

void dae::AudioSystem::AudioSystemImpl::Enqueue(const std::string& filename, int loops, int volume)
{
	std::lock_guard<std::mutex> lock(m_QueueMutex);
	m_pAudioQueue.push(new AudioClip(filename, loops, volume));
}

void dae::AudioSystem::AudioSystemImpl::CheckQueue()
{
	while (m_IsActive)
	{
		AudioClip* clip = nullptr;

		{
			std::lock_guard<std::mutex> lock(m_QueueMutex);
			if (!m_pAudioQueue.empty())
			{
				clip = m_pAudioQueue.front();
				m_pAudioQueue.pop();
			}
		}

		if (clip != nullptr)
		{
			if (LoadSound(clip))
			{
				PlaySound(clip);
				std::lock_guard<std::mutex> lock(m_ClipMutex);
				m_Clips.push_back(clip);
			}
			else
			{
				delete clip;
			}
		}
	}
}

void dae::AudioSystem::AudioSystemImpl::Mute(bool isMuted)
{
	if (isMuted)
	{
		Mix_Pause(-1);
	}
	else
	{
		Mix_Resume(-1);
	}
}

void dae::AudioSystem::AudioSystemImpl::PlaySound(AudioClip* clip)
{
	clip->Play();
}

bool dae::AudioSystem::AudioSystemImpl::LoadSound(AudioClip* clip)
{
	return clip->LoadWav();
}

dae::AudioSystem::AudioSystem()
	:m_pImpl(new AudioSystemImpl())
{

}

dae::AudioSystem::~AudioSystem()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

void dae::AudioSystem::Enqueue(const std::string& filename, int loops, int volume)
{
	m_pImpl->Enqueue(filename, loops, volume);
}

void dae::AudioSystem::CheckQueue()
{
	m_pImpl->CheckQueue();
}

void dae::AudioSystem::StopQueue()
{
	m_pImpl->StopQueue();
}

void dae::AudioSystem::Mute(bool isMuted)
{
	m_pImpl->Mute(isMuted);
}

void dae::LoggedAudioSystem::Enqueue(const std::string& filename, int loops, int volume)
{
	AudioSystem::Enqueue(filename, loops, volume);
}

void dae::LoggedAudioSystem::CheckQueue()
{
	AudioSystem::CheckQueue();
}

void dae::LoggedAudioSystem::StopQueue()
{
	AudioSystem::StopQueue();
}

void dae::LoggedAudioSystem::Mute(bool isMuted)
{
	AudioSystem::Mute(isMuted);
}