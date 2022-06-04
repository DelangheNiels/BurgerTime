#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		/*Scene& CreateScene(const std::string& name);*/

		void Update(float deltaTime);
		void FixedUpdate(float fixedTime);
		void Render();
		void AddScene(std::shared_ptr<Scene> scene);
		void NextScene();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;

		std::shared_ptr<Scene> m_ActiveScene{};
	};
}
