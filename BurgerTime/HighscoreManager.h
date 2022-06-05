#pragma once

#include "Singleton.h"

namespace dae
{
	class HighscoreManager final : public Singleton<HighscoreManager>
	{
	public:
		int GetHighScore();
		std::vector<int> GetTop10();
		void SaveScore() const;

		void SetCurrentScore(int score);
		int GetCurrentScore() const;

	private:
		friend class Singleton<HighscoreManager>;
		HighscoreManager() = default;

		void LoadScores();

		std::vector<int> m_Scores{};
		int m_HighScore{};
		bool m_Loaded{ false };

		int m_CurrentScore{};
	};
}


