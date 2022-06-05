#include "BurgerTimePCH.h"
#include "GameManager.h"

#include "SceneManager.h"

void dae::GameManager::AddPlayer(PeterPeperComponent* player)
{
	if (std::find(m_Players.begin(), m_Players.end(), player) == m_Players.end())
	{
		m_Players.push_back(player);
	}
}

void dae::GameManager::NotifyPlayerDied(PeterPeperComponent* player)
{
	if (std::find(m_Players.begin(), m_Players.end(), player) != m_Players.end())
	{
		++m_AmountOfDeadPlayers;

		if (m_AmountOfDeadPlayers == m_Players.size())
		{
			SceneManager::GetInstance().LoadScene("HighScoreScene");
		}
	}
}
