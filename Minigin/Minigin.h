#pragma once
//#include "AchievementSystem.h"
struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		float m_FixedTimeStep = 0.2f;
		SDL_Window* m_Window{};
		//AchievementSystem m_AchievementSystem = AchievementSystem();
	};
}