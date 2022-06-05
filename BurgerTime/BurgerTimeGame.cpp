#include "BurgerTimePCH.h"
#include "BurgerTimeGame.h"

#include "LevelLoader.h"

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
#include "PeterPeperComponent.h"
#include "PlayerHealthDisplayComponent.h"
#include "PointsComponent.h"
#include "PointsDisplayComponent.h"
#include"CollisionComponent.h"
#include "AnimatedSpriteComponent.h"
#include "BurgerPartComponent.h"
#include "BurgerComponent.h"
#include "EnemyComponent.h"

#include "MainMenuScene.h"
#include "GameScene.h"
#include "GameSceneMultiplayer.h"
#include "HighScoreScene.h"



void BurgerTimeGame::LoadGame() const
{
	SceneManager::GetInstance().AddScene(std::make_shared<MainMenuScene>("MainMenu"));
	SceneManager::GetInstance().AddScene(std::make_unique<GameScene>("SinglePlayerGame"));
	SceneManager::GetInstance().AddScene(std::make_unique<GameSceneMultiplayer>("MultiPlayerGame"));
	SceneManager::GetInstance().AddScene(std::make_unique<HighScoreScene>("HighScore"));

}

