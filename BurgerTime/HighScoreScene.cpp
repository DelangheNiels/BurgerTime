#include "BurgerTimePCH.h"
#include "HighScoreScene.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Command.h"

#include "HighscoreManager.h"
#include "InputManager.h"

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

		for (size_t i = 0; i < HighscoreManager::GetInstance().GetTop10().size(); ++i)
		{
			auto scoreObject = std::make_shared<GameObject>();
			auto scoreRenderComp = std::make_shared<RenderComponent>(scoreObject.get(), nullptr);
			std::string highscoreText = std::to_string(i + 1) + "# " + std::to_string(HighscoreManager::GetInstance().GetTop10()[i]);
			auto scoreTextComp = std::make_shared<TextComponent>(scoreObject.get(), highscoreText, highscoreFont, scoreRenderComp, SDL_Color{ 255,255,0 });
			scoreObject.get()->AddComponent(scoreRenderComp);
			scoreObject.get()->AddComponent(scoreTextComp);
			scoreObject.get()->SetPosition(330.0f, 140.0f + (40.0f * i));
			Add(scoreObject);
		}

		auto scoreObject = std::make_shared<GameObject>();
		auto scoreRenderComp = std::make_shared<RenderComponent>(scoreObject.get(), nullptr);
		std::string currentScoreText = "Score: " + std::to_string(HighscoreManager::GetInstance().GetCurrentScore());
		auto scoreTextComp = std::make_shared<TextComponent>(scoreObject.get(), currentScoreText, highscoreFont, scoreRenderComp, SDL_Color{ 255,255,0 });
		scoreObject.get()->AddComponent(scoreRenderComp);
		scoreObject.get()->AddComponent(scoreTextComp);
		scoreObject.get()->SetPosition(30, 650);
		Add(scoreObject);

		auto quitFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 40);
		auto quitObject = std::make_shared<GameObject>();
		auto quitRenderComp = std::make_shared<RenderComponent>(quitObject.get(), nullptr);
		auto quitTextComp = std::make_shared<TextComponent>(quitObject.get(), "Escape: Quit", quitFont, quitRenderComp, SDL_Color{ 255,255,255 });
		quitObject.get()->AddComponent(quitRenderComp);
		quitObject.get()->AddComponent(quitTextComp);
		quitObject.get()->SetPosition(500, 650);
		Add(quitObject);

		InputManager::GetInstance().AddKeyboardBinding<QuitCommand>(KeyboardButton::ESCAPE, nullptr);

		m_IsLoaded = true;
	}
	
}
