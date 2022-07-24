#include "MiniginPCH.h"
#include "AudioSystem.h"


class dae::AudioSystem::AudioSystemImpl final
{
public:
	AudioSystemImpl() = default;
	~AudioSystemImpl();
	AudioSystemImpl(const AudioSystemImpl& other) = delete;
	AudioSystemImpl(AudioSystemImpl&& other) noexcept = delete;
	AudioSystemImpl& operator=(const AudioSystemImpl& other) = delete;
	AudioSystemImpl& operator=(AudioSystemImpl&& other) noexcept = delete;

	void Enqueue(const std::string& filename, int loops = 0, int volume = 50);
	void CheckQueue();
	void StopQueue(){ m_IsActive = false; };

private:
	void PlaySound(AudioClip* clip);
	bool LoadSound(AudioClip* clip);

	std::mutex m_Mutex;
	std::queue<AudioClip*> m_pAudioQueue{};
	bool m_IsActive = true;
};

dae::AudioSystem::AudioSystemImpl::~AudioSystemImpl()
{
	for (size_t i = 0; i < m_pAudioQueue.size(); ++i)
	{
		m_pAudioQueue.pop();
	}
}

void dae::AudioSystem::AudioSystemImpl::Enqueue(const std::string& filename, int loops, int volume)
{
	m_Mutex.lock();
	m_pAudioQueue.push(new AudioClip(filename, loops, volume));
	m_Mutex.unlock();
}

void dae::AudioSystem::AudioSystemImpl::CheckQueue()
{
	std::vector<AudioClip*> clips{};
	while (m_IsActive)
	{
		if (!m_pAudioQueue.empty())
		{
			m_Mutex.lock();
			clips.push_back(m_pAudioQueue.front());
			m_pAudioQueue.pop();
			m_Mutex.unlock();
			if (LoadSound(clips.front()))
			{
				PlaySound(clips.front());
			}
		}
		if (!clips.empty())
		{
			for (size_t i = 0; i < clips.size(); ++i)
			{
				if (clips[i]->IsPlaying()){continue;}
				delete clips[i];
				clips[i] = nullptr;
				clips.erase(clips.begin() + i);
			}
		}
	}
	for (auto ac : clips)
	{
		delete ac;
		ac = nullptr;
	}
	clips.clear();
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
	Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048);
	m_thread = std::thread(&AudioSystem::CheckQueue, this);
}

dae::AudioSystem::~AudioSystem()
{
	m_thread.join();
	Mix_CloseAudio();
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
