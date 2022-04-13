#pragma once

#include "AchievementObserver.h"
#include "Component.h"
#include "CSteamAchievements.h"
class PointsAchievementObserver : public AchievementObserver, public dae::Component
{
public:

	PointsAchievementObserver(dae::GameObject* gameObject, CSteamAchievements* steamAchievements);
	void AddScore(int score) override;
	void Update(float deltaTime) override;

private:
	int m_TotalScore;
	CSteamAchievements* m_pSteamAchievements;

};

