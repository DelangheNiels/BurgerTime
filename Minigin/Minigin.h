#pragma once
//#include "AchievementSystem.h"
#include "Scene.h"
struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		virtual void LoadGame() const = 0;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		float m_FixedTimeStep = 0.2f;
		SDL_Window* m_Window{};
		//AchievementSystem m_AchievementSystem = AchievementSystem();

		void CreateLevel(Scene& scene) const;
		void CreatePlatform(Scene& scene, float x, float y, std::string texture) const;
		void CreateLadder(Scene& scene, float x, float y, std::string texture) const;
	};
}