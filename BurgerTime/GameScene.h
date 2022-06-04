#pragma once

#include "Scene.h"
namespace dae
{
	class GameScene final : public Scene
	{
	public:
		GameScene(const std::string& name);

		void LoadScene() override;
	};
}


