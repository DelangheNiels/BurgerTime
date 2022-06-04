#pragma once
#include "SceneManager.h"

namespace dae
{
	class SceneObject;
	class GameObject;
	class Scene
	{
		//friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		void Update(float deltaTime);
		void FixedUpdate(float fixedTime);
		void Render() const;

		void SetActive();
		void SetInActive();
		bool GetIsActive();

		explicit Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		virtual void LoadScene();

	private: 
		
		bool m_IsActive{};

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter; 

		void HandleCollisions();
	};

}
