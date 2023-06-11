#pragma once
#include <string>
#include "SDL_mixer.h"

class AudioClip final
{
public:
	explicit AudioClip(const std::string& path, int loops, int volume);
	~AudioClip();
	AudioClip(const AudioClip& other) = delete;
	AudioClip(AudioClip&& other) = delete;
	AudioClip& operator=(const AudioClip& other) = delete;
	AudioClip& operator=(AudioClip&& other) noexcept = delete;
	bool operator==(const AudioClip&) const;

	bool LoadWav();
	void SetVolume(const int volume);
	void Play();
	void Pause() const;
	void Resume() const;
	bool IsPlaying() const;
private:
	std::string m_FilePath;
	Mix_Chunk* m_pChunk = nullptr;
	int m_Volume;
	int m_Loops;
	int m_Channel = 0;
};

