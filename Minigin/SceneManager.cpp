#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	if (m_ActiveScene)
	{
		m_ActiveScene.get()->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float fixedTime)
{
	if (m_ActiveScene)
	{
		m_ActiveScene.get()->FixedUpdate(fixedTime);
	}
}

void dae::SceneManager::Render()
{
	
	if (m_ActiveScene)
	{
		m_ActiveScene.get()->Render();
	}
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	if (m_Scenes.size() == 0)
	{
		m_ActiveScene = scene;
		scene.get()->SetActive();
	}

	m_Scenes.push_back(scene);
}

void dae::SceneManager::NextScene()
{
	if (m_ActiveScene != nullptr && m_Scenes.size() > 1)
	{
		m_ActiveScene.get()->SetInActive();

		auto itr = std::find(m_Scenes.begin(), m_Scenes.end(), m_ActiveScene);
		int index = int(itr - m_Scenes.begin());
		if (index < m_Scenes.size() - 1)
		{
			m_ActiveScene = m_Scenes[index+1];
		}

		else
		{
			m_ActiveScene = m_Scenes[0];
		}

		m_ActiveScene.get()->SetActive();
	}
}

//dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
//{
//	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
//	m_Scenes.push_back(scene);
//
//	if (m_Scenes.size() == 1)
//	{
//		m_ActiveScene = scene;
//	}
//	return *scene;
//}
