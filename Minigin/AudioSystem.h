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
	class AudioSystemAbs
	{
	public:
		AudioSystemAbs() = default;
		virtual ~AudioSystemAbs() = default;
		AudioSystemAbs(const AudioSystemAbs& other) = delete;
		AudioSystemAbs(AudioSystemAbs&& other) noexcept = delete;
		AudioSystemAbs& operator=(const AudioSystemAbs& other) = delete;
		AudioSystemAbs& operator=(AudioSystemAbs&& other) noexcept = delete;

		virtual void Enqueue(const std::string& filename, int loops = 0, int volume = 50) = 0;
		virtual void CheckQueue() = 0;
		virtual void StopQueue() = 0;
	};
	class NullAudioSystem final : public AudioSystemAbs
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
		void StopQueue() override{}
	};

	class AudioSystem final : public AudioSystemAbs
	{
	public:
		AudioSystem();
		~AudioSystem() override;
		AudioSystem(const AudioSystem& other) = delete;
		AudioSystem(AudioSystem&& other) noexcept = delete;
		AudioSystem& operator=(const AudioSystem& other) = delete;
		AudioSystem& operator=(AudioSystem&& other) noexcept = delete;

		void Enqueue(const std::string& filename, int loops = 0, int volume = 50) override;
		void CheckQueue() override;
		void StopQueue() override;

	private:
		class AudioSystemImpl;
		AudioSystemImpl* m_pImpl = nullptr;
		std::thread m_thread;
	};
}
