#include "MiniginPCH.h"
#include "AchievementSystem.h"

AchievementSystem::AchievementSystem()
{
	m_pSteamAchievements = new CSteamAchievements(g_Achievements, 4);
}

AchievementSystem::~AchievementSystem()
{
	delete m_pSteamAchievements;
}

CSteamAchievements* AchievementSystem::GetSteamAchievements() const
{
	return m_pSteamAchievements;
}
