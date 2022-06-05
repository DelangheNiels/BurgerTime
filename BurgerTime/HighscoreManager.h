#pragma once

#include "Singleton.h"

namespace dae
{
	class HighscoreManager final : public Singleton<HighscoreManager>
	{
	public:
		int GetHighScore();
		std::vector<int> GetTop10();
		void SaveScore(int score);
	private:
		friend class Singleton<HighscoreManager>;
		HighscoreManager() = default;

		void LoadScores();

		std::vector<int> m_Scores{};
		int m_HighScore{};
		bool m_Loaded{ false };
	};
}


