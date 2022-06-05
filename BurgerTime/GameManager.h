#pragma once
#include "Singleton.h"

#include <vector>

namespace dae
{
	class PeterPeperComponent;

	class GameManager final : public Singleton<GameManager>
	{
	public:

		void AddPlayer(PeterPeperComponent* player);
		void NotifyPlayerDied(PeterPeperComponent* player);

	private:
		friend class Singleton<GameManager>;
		GameManager() = default;

		std::vector<PeterPeperComponent*> m_Players;
		int m_AmountOfDeadPlayers{ 0 };
	};
}



