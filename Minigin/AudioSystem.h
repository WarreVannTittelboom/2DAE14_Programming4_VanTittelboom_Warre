#pragma once
#include <map>
#include <queue>
#include <mutex>
#include <stack>
#include <vector>
#include <memory>
#include <iostream>
#include "SDL_mixer.h"
#include "AudioClip.h"
#include "InputManager.h"

using namespace std::literals::chrono_literals;


namespace dae
{
	class AudioSystem
	{
	public:
		AudioSystem();
		virtual ~AudioSystem();
		AudioSystem(const AudioSystem& other) = delete;
		AudioSystem(AudioSystem&& other) noexcept = delete;
		AudioSystem& operator=(const AudioSystem& other) = delete;
		AudioSystem& operator=(AudioSystem&& other) noexcept = delete;

		virtual void Enqueue(const std::string& filename, int loops = 0, int volume = 50);
		virtual void CheckQueue();
		virtual void StopQueue();
		virtual void Mute(bool isMuted);

	protected:
		class AudioSystemImpl;
		AudioSystemImpl* m_pImpl = nullptr;
	};
	class NullAudioSystem final : public AudioSystem
	{
	public:
		NullAudioSystem() = default;
		~NullAudioSystem() override = default;
		NullAudioSystem(const NullAudioSystem& other) = delete;
		NullAudioSystem(NullAudioSystem&& other) noexcept = delete;
		NullAudioSystem& operator=(const NullAudioSystem& other) = delete;
		NullAudioSystem& operator=(NullAudioSystem&& other) noexcept = delete;

		void Enqueue(const std::string&, int = 0, int = 50)override {}
		void CheckQueue() override {}
		void StopQueue() override {}
		void Mute(bool isMuted)override {};
	};

	class LoggedAudioSystem final : public AudioSystem
	{
	public:
		LoggedAudioSystem() = default;
		~LoggedAudioSystem() override = default;
		LoggedAudioSystem(const LoggedAudioSystem& other) = delete;
		LoggedAudioSystem(LoggedAudioSystem&& other) noexcept = delete;
		LoggedAudioSystem& operator=(const LoggedAudioSystem& other) = delete;
		LoggedAudioSystem& operator=(LoggedAudioSystem&& other) noexcept = delete;

		void Enqueue(const std::string& filename, int loops = 0, int volume = 50) override;
		void CheckQueue() override;
		void StopQueue() override;
		void Mute(bool isMuted)override;
	};
}