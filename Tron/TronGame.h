#pragma once
#include "Singleton.h"
#include <memory>
#include "Scene.h"
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

		void ReadJsonFile(const std::string& name,Scene& scene);

		int m_Score = 0;
		int m_Lives = 1;
	};
}

