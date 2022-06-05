#include "BurgerTimePCH.h"

#include "HighscoreManager.h"

#include <fstream>
#include <algorithm>

int dae::HighscoreManager::GetHighScore()
{
    if (!m_Loaded)
    {
        LoadScores();
        m_Loaded = true;
    }
    return m_HighScore;
}

std::vector<int> dae::HighscoreManager::GetTop10() const
{
    return m_Scores;
}

void dae::HighscoreManager::SaveScore(int)
{
}

void dae::HighscoreManager::LoadScores()
{
    std::ifstream file("../Data/TextFiles/HighScores.txt");

    if (!file)
    {
        std::cout << "highscore file not found" << "\n";
        return;
    }

    while (!file.eof())
    {
        int score{};
        file >> score;
        m_Scores.push_back(score);
    }

    //sort scores from high to low
    std::sort(m_Scores.begin(), m_Scores.end(), [](int s1, int s2) {return s1 > s2; });
    m_HighScore = m_Scores[0];
}
