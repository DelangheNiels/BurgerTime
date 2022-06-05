#include "BurgerTimePCH.h"
#include "MainMenuScene.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Command.h"
#include "GameCommands.h"
#include "ServiceLocator.h"
#include "ServiceLocator.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"


dae::MainMenuScene::MainMenuScene(const std::string& name)
	:Scene(name)
{
	LoadScene();
}

void dae::MainMenuScene::LoadScene()
{
	if (!m_IsLoaded)
	{
		ServiceLocator::GetSoundService().QueueAudioClip(ResourceManager::GetInstance().LoadSound("StartMusic.mp3"), 0.3f,false);

		//backgroundImage
		auto backgroundImageObject = std::make_shared<GameObject>();
		backgroundImageObject.get()->AddComponent(std::make_shared<RenderComponent>(backgroundImageObject.get(), ResourceManager::GetInstance().LoadTexture("StartScreen.png")));
		Add(backgroundImageObject);


		//fps counter
		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
		auto fpsGameObject = std::make_shared<GameObject>();
		const SDL_Color color = { 255,255,0 };
		auto renderComp = std::make_shared<RenderComponent>(fpsGameObject.get(), nullptr);
		auto textComp = std::make_shared<TextComponent>(fpsGameObject.get(), "FPS: 0", font, renderComp, color);
		fpsGameObject.get()->AddComponent(renderComp);
		fpsGameObject.get()->AddComponent(textComp);
		fpsGameObject.get()->AddComponent(std::make_shared<FPSComponent>(fpsGameObject.get(), textComp));
		fpsGameObject.get()->SetPosition(2, 10);
		Add(fpsGameObject);

		auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto singlePlayerObject = std::make_shared<GameObject>();
		auto renderComp2 = std::make_shared<RenderComponent>(singlePlayerObject.get(), nullptr);
		auto textComp2 = std::make_shared<TextComponent>(singlePlayerObject.get(), "F1: Single Player", font2, renderComp2, color);
		singlePlayerObject.get()->AddComponent(renderComp2);
		singlePlayerObject.get()->AddComponent(textComp2);
		singlePlayerObject.get()->SetPosition(90, 400);
		Add(singlePlayerObject);

		auto multiPlayerObject = std::make_shared<GameObject>();
		auto renderComp3 = std::make_shared<RenderComponent>(multiPlayerObject.get(), nullptr);
		auto textComp3 = std::make_shared<TextComponent>(multiPlayerObject.get(), "F2: Co-op", font2, renderComp3, color);
		multiPlayerObject.get()->AddComponent(renderComp3);
		multiPlayerObject.get()->AddComponent(textComp3);
		multiPlayerObject.get()->SetPosition(90, 500);
		Add(multiPlayerObject);

		//input commands
		InputManager::GetInstance().AddKeyboardBinding<SelectSinglePlayerCommand>(KeyboardButton::F1, nullptr);
		InputManager::GetInstance().AddKeyboardBinding<SelectMultiPlayerCommand>(KeyboardButton::F2, nullptr);

		m_IsLoaded = true;
	}
	

}

