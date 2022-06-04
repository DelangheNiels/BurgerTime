#pragma once

#include "Scene.h"

namespace dae
{
	class GameSceneMultiplayer final : public Scene
	{
	public:
		GameSceneMultiplayer(const std::string& name);
		~GameSceneMultiplayer() = default;
		GameSceneMultiplayer(const GameSceneMultiplayer& other) = delete;
		GameSceneMultiplayer(GameSceneMultiplayer&& other) = delete;
		GameSceneMultiplayer& operator=(const GameSceneMultiplayer& other) = delete;
		GameSceneMultiplayer& operator=(GameSceneMultiplayer&& other) = delete;

		void LoadScene() override;
	};
}


