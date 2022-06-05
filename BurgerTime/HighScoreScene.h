#pragma once

#include "Scene.h"

namespace dae
{
	class HighScoreScene final : public Scene
	{
	public:
		HighScoreScene(const std::string& name);
		~HighScoreScene() = default;
		HighScoreScene(const HighScoreScene & other) = delete;
		HighScoreScene(HighScoreScene && other) = delete;
		HighScoreScene& operator=(const HighScoreScene & other) = delete;
		HighScoreScene& operator=(HighScoreScene && other) = delete;

		void LoadScene() override;
	};

}

