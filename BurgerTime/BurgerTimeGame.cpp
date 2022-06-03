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




void BurgerTimeGame::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Load level
	LevelLoader loader = LevelLoader("Level.txt");
	loader.LoadLevel(scene);
	//CreateLevel(scene);

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
	scene.Add(fpsGameObject);


	//PeterPeper GameObject
	auto peterPeperGameObject = std::make_shared<GameObject>();
	peterPeperGameObject.get()->SetTag("Player");

	auto spriteRenderComp = std::make_shared<RenderComponent>(peterPeperGameObject.get(), ResourceManager::GetInstance().LoadTexture("PlayerIdle.png"));
	BoundingBox collisionBox{ spriteRenderComp.get()->GetWidth(), spriteRenderComp.get()->GetHeight() };
	auto collisionComponent = std::make_shared<CollisionComponent>(peterPeperGameObject.get(), collisionBox);

	auto idleAnimation = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject.get(), spriteRenderComp.get(), 1, ResourceManager::GetInstance().LoadSpriteSheet("PlayerIdle.png"));
	auto walkLeftAnimation = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject.get(), spriteRenderComp.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("SpriteSheets/PlayerSprites/PlayerWalkingLeft.png"));
	auto walkRightAnimation = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject.get(), spriteRenderComp.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("SpriteSheets/PlayerSprites/PlayerWalkingRight.png"));
	auto walkUpAnimation = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject.get(), spriteRenderComp.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("SpriteSheets/PlayerSprites/PlayerWalkingUp.png"));
	auto walkDownAnimation = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject.get(), spriteRenderComp.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("SpriteSheets/PlayerSprites/PlayerWalkingDown.png"));
	std::map<PlayerStates, AnimatedSpriteComponent*> animations;
	
	animations.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::Idle, idleAnimation.get()));
	animations.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::WalkingLeft, walkLeftAnimation.get()));
	animations.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::WalkingRight, walkRightAnimation.get()));
	animations.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::ClimbingUp, walkUpAnimation.get()));
	animations.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::ClimbingDown, walkDownAnimation.get()));

	auto playerOne = std::make_shared<PeterPeperComponent>(peterPeperGameObject.get(), 3, spriteRenderComp.get(), animations);

	peterPeperGameObject.get()->AddComponent(playerOne);
	peterPeperGameObject.get()->AddComponent(spriteRenderComp);
	peterPeperGameObject.get()->AddComponent(collisionComponent);
	peterPeperGameObject.get()->AddComponent(idleAnimation);
	peterPeperGameObject.get()->AddComponent(walkLeftAnimation);
	peterPeperGameObject.get()->AddComponent(walkRightAnimation);
	peterPeperGameObject.get()->AddComponent(walkUpAnimation);
	peterPeperGameObject.get()->AddComponent(walkDownAnimation);
	
	peterPeperGameObject.get()->SetPosition(55, 61);
	//peterPeperGameObject.get()->SetPosition(375, 545);
	scene.Add(peterPeperGameObject);

	//player One lives display
	auto playerOneHealthDisplayObject = std::make_shared<GameObject>();

	const SDL_Color colorP1 = { 255,255,0 };
	auto renderCompHealthP1 = std::make_shared<RenderComponent>(playerOneHealthDisplayObject.get(), nullptr);
	auto textCompHealthP1 = std::make_shared<TextComponent>(playerOneHealthDisplayObject.get(), "", font, renderCompHealthP1, colorP1);

	auto playerOneHealthDisplayComponent = std::make_shared<PlayerHealthDisplayComponent>(playerOneHealthDisplayObject.get(), playerOne.get(), textCompHealthP1);

	playerOneHealthDisplayObject.get()->AddComponent(playerOneHealthDisplayComponent);
	playerOneHealthDisplayObject.get()->AddComponent(renderCompHealthP1);
	playerOneHealthDisplayObject.get()->AddComponent(textCompHealthP1);
	playerOneHealthDisplayObject.get()->SetPosition(150, 10);
	scene.Add(playerOneHealthDisplayObject);

	//points display player one
	auto pointsDisplayPlayerOneGameObject = std::make_shared<GameObject>();
	auto renderCompPointsP1 = std::make_shared<RenderComponent>(pointsDisplayPlayerOneGameObject.get(), nullptr);
	auto textCompPointsP1 = std::make_shared<TextComponent>(pointsDisplayPlayerOneGameObject.get(), "", font, renderCompPointsP1, colorP1);

	auto pointsComponent = std::make_shared<PointsComponent>(pointsDisplayPlayerOneGameObject.get(), 50/*, pointsAchievementObserver.get()*/);
	auto pointsDisplayComponent = std::make_shared<PointsDisplayComponent>(pointsDisplayPlayerOneGameObject.get(), textCompPointsP1);
	pointsComponent.get()->AddPointsObserver(pointsDisplayComponent.get());

	pointsDisplayPlayerOneGameObject.get()->AddComponent(renderCompPointsP1);
	pointsDisplayPlayerOneGameObject.get()->AddComponent(textCompPointsP1);
	pointsDisplayPlayerOneGameObject.get()->AddComponent(pointsComponent);
	pointsDisplayPlayerOneGameObject.get()->AddComponent(pointsDisplayComponent);
	pointsDisplayPlayerOneGameObject.get()->SetPosition(225, 10);
	scene.Add(pointsDisplayPlayerOneGameObject);

	////Player2
	//auto peterPeperGameObject2 = std::make_shared<GameObject>();
	//auto player2 = std::make_shared<PeterPeperComponent>(peterPeperGameObject2.get(), 3);
	//auto spriteRenderComp2 = std::make_shared<RenderComponent>(peterPeperGameObject2.get(), nullptr);
	//peterPeperGameObject2.get()->AddComponent(player2);
	//peterPeperGameObject2.get()->AddComponent(spriteRenderComp2);
	//scene.Add(peterPeperGameObject2);

	////player 2 lives display
	//auto player2HealthDisplayObject = std::make_shared<GameObject>();

	//const SDL_Color colorP2 = { 0,255,0 };
	//auto renderCompHealthP2 = std::make_shared<RenderComponent>(player2HealthDisplayObject.get(), nullptr);
	//auto textCompHealthP2 = std::make_shared<TextComponent>(player2HealthDisplayObject.get(), "", font, renderCompHealthP2, colorP2);

	//auto player2HealthDisplayComponent = std::make_shared<PlayerHealthDisplayComponent>(player2HealthDisplayObject.get(), player2.get(), textCompHealthP2);

	//player2HealthDisplayObject.get()->AddComponent(player2HealthDisplayComponent);
	//player2HealthDisplayObject.get()->AddComponent(renderCompHealthP2);
	//player2HealthDisplayObject.get()->AddComponent(textCompHealthP2);
	//player2HealthDisplayObject.get()->SetPosition(550, 10);
	//scene.Add(player2HealthDisplayObject);

	////points display player 2
	//auto pointsDisplayPlayer2GameObject = std::make_shared<GameObject>();
	//auto renderCompPointsP2 = std::make_shared<RenderComponent>(pointsDisplayPlayer2GameObject.get(), nullptr);
	//auto textCompPointsP2 = std::make_shared<TextComponent>(pointsDisplayPlayer2GameObject.get(), "", font, renderCompPointsP2, colorP2);

	//auto pointsComponent2 = std::make_shared<PointsComponent>(pointsDisplayPlayer2GameObject.get(), 50 /*pointsAchievementObserver.get()*/);
	//auto pointsDisplayComponent2 = std::make_shared<PointsDisplayComponent>(pointsDisplayPlayer2GameObject.get(), textCompPointsP2);
	//pointsComponent2.get()->AddPointsObserver(pointsDisplayComponent2.get());

	//pointsDisplayPlayer2GameObject.get()->AddComponent(renderCompPointsP2);
	//pointsDisplayPlayer2GameObject.get()->AddComponent(textCompPointsP2);
	//pointsDisplayPlayer2GameObject.get()->AddComponent(pointsComponent2);
	//pointsDisplayPlayer2GameObject.get()->AddComponent(pointsDisplayComponent2);
	//pointsDisplayPlayer2GameObject.get()->SetPosition(625, 10);
	//scene.Add(pointsDisplayPlayer2GameObject);



	//input commands
	InputManager::GetInstance().AddController(new XBox360Controller{ 0 });
	InputManager::GetInstance().AddController(new XBox360Controller{ 1 });
	//player 1 inputs
	InputManager::GetInstance().AddControllerCommandBinding<HitCommand>(ControllerButton::ButtonA, peterPeperGameObject.get(), 0);
	InputManager::GetInstance().AddControllerCommandBinding<PointsCommand>(ControllerButton::ButtonB, pointsDisplayPlayerOneGameObject.get(), 0);
	InputManager::GetInstance().AddControllerCommandBinding<MoveLeftCommand>(ControllerButton::ButtonLeft, peterPeperGameObject.get(), 0);
	InputManager::GetInstance().AddControllerCommandBinding<MoveRightCommand>(ControllerButton::ButtonRight, peterPeperGameObject.get(), 0);
	InputManager::GetInstance().AddControllerCommandBinding<MoveUpCommand>(ControllerButton::ButtonUp, peterPeperGameObject.get(), 0);
	InputManager::GetInstance().AddControllerCommandBinding<MoveDownCommand>(ControllerButton::ButtonDown, peterPeperGameObject.get(), 0);
	InputManager::GetInstance().AddKeyboardBinding<HitCommand>(KeyboardButton::Q, peterPeperGameObject.get());
	////player2 inputs
	//InputManager::GetInstance().AddControllerCommandBinding<HitCommand>(ControllerButton::ButtonX, peterPeperGameObject2.get(), 1);
	//InputManager::GetInstance().AddControllerCommandBinding<PointsCommand>(ControllerButton::ButtonY, pointsDisplayPlayer2GameObject.get(), 1);

	std::cout << "Used controlls:" << "\n";
	std::cout << "======================" << "\n";
	std::cout << "Player1:" << "\n";
	std::cout << "Damage: A" << "\n";
	std::cout << "Points: B" << "\n";
	std::cout << "Horizontal Movement: left/right D-Pad" << "\n";
	std::cout << "Play sound: D-Pad up" << "\n";
	std::cout << "======================" << "\n";
	std::cout << "Player2:" << "\n";
	std::cout << "Damage: X" << "\n";
	std::cout << "Points: Y" << "\n";
	std::cout << "======================" << "\n";
}