#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	/*for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}*/

	if (m_ActiveScene)
	{
		m_ActiveScene.get()->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float fixedTime)
{
	/*for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(fixedTime);
	}*/

	if (m_ActiveScene)
	{
		m_ActiveScene.get()->FixedUpdate(fixedTime);
	}
}

void dae::SceneManager::Render()
{
	/*for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}*/

	if (m_ActiveScene)
	{
		m_ActiveScene.get()->Render();
	}
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_Scenes.push_back(scene);

	if (m_Scenes.size() == 1)
	{
		m_ActiveScene = scene;
	}
}
