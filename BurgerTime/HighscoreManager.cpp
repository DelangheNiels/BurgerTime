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

std::vector<int> dae::HighscoreManager::GetTop10()
{

    if (!m_Loaded)
    {
        LoadScores();
        m_Loaded = true;
    }

    if (m_Scores.size() <= 10)
    {
        return m_Scores;
    }

    else
    {
        std::vector<int> scores{};
        for (int i = 0; i < 10; i++)
        {
            scores.push_back(m_Scores[i]);
        }
        return scores;
    }
    
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
