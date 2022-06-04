#pragma once

#include "Scene.h"
namespace dae 
{
	class MainMenuScene final : public Scene
	{
	public:
		MainMenuScene(const std::string& name);
		~MainMenuScene() = default;
		MainMenuScene(const MainMenuScene& other) = delete;
		MainMenuScene(MainMenuScene&& other) = delete;
		MainMenuScene& operator=(const MainMenuScene& other) = delete;
		MainMenuScene& operator=(MainMenuScene&& other) = delete;
		
		void LoadScene() override;
	};
}


