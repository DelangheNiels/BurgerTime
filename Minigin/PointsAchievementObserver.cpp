#include "MiniginPCH.h"
#include "PointsAchievementObserver.h"

PointsAchievementObserver::PointsAchievementObserver(dae::GameObject* gameObject, CSteamAchievements* steamAchievements)
	:Component(gameObject), m_TotalScore{0}, m_pSteamAchievements{steamAchievements}
{
}

void PointsAchievementObserver::AddScore(int score)
{
	
	m_TotalScore += score;

	if (m_TotalScore == 500)
	{
		m_pSteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
	}
}

void PointsAchievementObserver::Update(float)
{
}
