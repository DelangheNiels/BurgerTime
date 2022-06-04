#pragma once

#include "Scene.h"
namespace dae
{
	class GameScene final : public Scene
	{
	public:
		GameScene(const std::string& name);
		~GameScene() = default;
		GameScene(const GameScene& other) = delete;
		GameScene(GameScene&& other) = delete;
		GameScene& operator=(const GameScene& other) = delete;
		GameScene& operator=(GameScene&& other) = delete;

		void LoadScene() override;
	};
}


