#include "BurgerTimePCH.h"
#include "HighScoreScene.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"

#include "HighscoreManager.h"

dae::HighScoreScene::HighScoreScene(const std::string& name)
	:Scene(name)
{
	//LoadScene();
}

void dae::HighScoreScene::LoadScene()
{
	if (!m_IsLoaded)
	{
		auto titleFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 50);
		auto titleObject = std::make_shared<GameObject>();
		auto titleRenderComp = std::make_shared<RenderComponent>(titleObject.get(), nullptr);
		auto titleTextComp = std::make_shared<TextComponent>(titleObject.get(), "Top 10 Scores", titleFont, titleRenderComp, SDL_Color{ 255,255,255 });
		titleObject.get()->AddComponent(titleRenderComp);
		titleObject.get()->AddComponent(titleTextComp);
		titleObject.get()->SetPosition(230, 50);
		Add(titleObject);

		auto highscoreFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

		for (int i = 0; i < HighscoreManager::GetInstance().GetTop10().size(); ++i)
		{
			auto scoreObject = std::make_shared<GameObject>();
			auto scoreRenderComp = std::make_shared<RenderComponent>(scoreObject.get(), nullptr);
			std::string highscoreText = std::to_string(i + 1) + "# " + std::to_string(HighscoreManager::GetInstance().GetTop10()[i]);
			auto scoreTextComp = std::make_shared<TextComponent>(scoreObject.get(), highscoreText, highscoreFont, scoreRenderComp, SDL_Color{ 255,255,0 });
			scoreObject.get()->AddComponent(scoreRenderComp);
			scoreObject.get()->AddComponent(scoreTextComp);
			scoreObject.get()->SetPosition(330, 140 + (40 * i));
			Add(scoreObject);
		}

		m_IsLoaded = true;
	}
	
}
