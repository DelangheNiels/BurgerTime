#include "BurgerTimePCH.h"
#include "MainMenuScene.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Command.h"
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

	//input commands
	InputManager::GetInstance().AddKeyboardBinding<LoadSinglePlayerScene>(KeyboardButton::F1, nullptr);
	InputManager::GetInstance().AddKeyboardBinding<LoadMultiPlayerScene>(KeyboardButton::F2, nullptr);

}

