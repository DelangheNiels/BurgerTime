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

void dae::HighscoreManager::SaveScore() const
{
    std::ofstream file("../Data/TextFiles/HighScores.txt");

    if (file.is_open())
    {
        for (size_t i = 0; i < m_Scores.size(); i++)
        {
            std::string line = std::to_string(m_Scores[i]) + "\n";
            file << line;
        }

        std::string line = std::to_string(m_CurrentScore) + "\n";
        file << line;

        file.close();
    }
}

void dae::HighscoreManager::SetCurrentScore(int score)
{
    m_CurrentScore = score;
}

int dae::HighscoreManager::GetCurrentScore() const
{
    return m_CurrentScore;
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
