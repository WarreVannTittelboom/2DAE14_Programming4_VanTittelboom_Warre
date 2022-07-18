#pragma once
#include "Singleton.h"

namespace dae
{
	class TronGame : public Singleton<TronGame>
	{
	public:
		TronGame() = default;
		~TronGame() = default;
		TronGame(const TronGame& other) = delete;
		TronGame(TronGame&& other) noexcept = delete;
		TronGame& operator=(const TronGame& other) = delete;
		TronGame& operator=(TronGame&& other) noexcept = delete;

		void CreateScenes();
	};
}

