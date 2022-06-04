#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void Update(float deltaTime);
		void FixedUpdate(float fixedTime);
		void Render();
		void AddScene(std::shared_ptr<Scene> scene);
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;

		std::shared_ptr<Scene> m_ActiveScene{};
	};
}
