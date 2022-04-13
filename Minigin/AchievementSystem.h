#pragma once
#include "steam_api.h"
#include "AchievementStruct.h"
#include "CSteamAchievements.h"
class AchievementSystem
{
public:

	AchievementSystem();
	~AchievementSystem();

	CSteamAchievements* GetSteamAchievements() const;

	enum EAchievements
	{
		ACH_WIN_ONE_GAME = 0,
		ACH_WIN_100_GAMES = 1,
		ACH_TRAVEL_FAR_ACCUM = 2,
		ACH_TRAVEL_FAR_SINGLE = 3,
	};

	

private:
	// Achievement array which will hold data about the achievements and their state
	Achievement_t g_Achievements[4] =
	{
		_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
		_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
		_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
		_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
	};

	CSteamAchievements* m_pSteamAchievements = NULL;
};

