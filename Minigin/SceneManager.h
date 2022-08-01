#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void SetScene(const std::string& name);
		Scene& GetScene(const std::string& name);
		Scene& GetActiveScene();
		void Update();
		void FixedUpdate(float fDT);
		void LateUpdate();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		~SceneManager();
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
