#pragma once
#include "Singleton.h"
#include <memory>
#include "Scene.h"
namespace dae
{
	class PlayerTank;
	class TextComp;
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

		void ReadJsonFileReset(const std::string& name, dae::Scene& scene,GameObject* tank);

		void ResetLevel();

		int m_Score = 0;
		int m_LivesP1 = 4;
		int m_LivesP2 = 4;
	};
}

