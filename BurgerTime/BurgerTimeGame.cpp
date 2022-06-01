#include "BurgerTimePCH.h"
#include "BurgerTimeGame.h"

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


void BurgerTimeGame::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	CreateLevel(scene);

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
	auto playerOne = std::make_shared<PeterPeperComponent>(peterPeperGameObject.get(), 3);
	auto spriteRenderComp = std::make_shared<RenderComponent>(peterPeperGameObject.get(), ResourceManager::GetInstance().LoadTexture("PlayerIdle.png"));
	BoundingBox collisionBox{ spriteRenderComp.get()->GetWidth(), spriteRenderComp.get()->GetHeight()};
	auto collisionComponent = std::make_shared<CollisionComponent>(peterPeperGameObject.get(), collisionBox);
	peterPeperGameObject.get()->AddComponent(playerOne);
	peterPeperGameObject.get()->AddComponent(spriteRenderComp);
	peterPeperGameObject.get()->AddComponent(collisionComponent);
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

	//Player2
	auto peterPeperGameObject2 = std::make_shared<GameObject>();
	auto player2 = std::make_shared<PeterPeperComponent>(peterPeperGameObject2.get(), 3);
	auto spriteRenderComp2 = std::make_shared<RenderComponent>(peterPeperGameObject2.get(), nullptr);
	peterPeperGameObject2.get()->AddComponent(player2);
	peterPeperGameObject2.get()->AddComponent(spriteRenderComp2);
	scene.Add(peterPeperGameObject2);

	//player 2 lives display
	auto player2HealthDisplayObject = std::make_shared<GameObject>();

	const SDL_Color colorP2 = { 0,255,0 };
	auto renderCompHealthP2 = std::make_shared<RenderComponent>(player2HealthDisplayObject.get(), nullptr);
	auto textCompHealthP2 = std::make_shared<TextComponent>(player2HealthDisplayObject.get(), "", font, renderCompHealthP2, colorP2);

	auto player2HealthDisplayComponent = std::make_shared<PlayerHealthDisplayComponent>(player2HealthDisplayObject.get(), player2.get(), textCompHealthP2);

	player2HealthDisplayObject.get()->AddComponent(player2HealthDisplayComponent);
	player2HealthDisplayObject.get()->AddComponent(renderCompHealthP2);
	player2HealthDisplayObject.get()->AddComponent(textCompHealthP2);
	player2HealthDisplayObject.get()->SetPosition(550, 10);
	scene.Add(player2HealthDisplayObject);

	//points display player 2
	auto pointsDisplayPlayer2GameObject = std::make_shared<GameObject>();
	auto renderCompPointsP2 = std::make_shared<RenderComponent>(pointsDisplayPlayer2GameObject.get(), nullptr);
	auto textCompPointsP2 = std::make_shared<TextComponent>(pointsDisplayPlayer2GameObject.get(), "", font, renderCompPointsP2, colorP2);

	auto pointsComponent2 = std::make_shared<PointsComponent>(pointsDisplayPlayer2GameObject.get(), 50 /*pointsAchievementObserver.get()*/);
	auto pointsDisplayComponent2 = std::make_shared<PointsDisplayComponent>(pointsDisplayPlayer2GameObject.get(), textCompPointsP2);
	pointsComponent2.get()->AddPointsObserver(pointsDisplayComponent2.get());

	pointsDisplayPlayer2GameObject.get()->AddComponent(renderCompPointsP2);
	pointsDisplayPlayer2GameObject.get()->AddComponent(textCompPointsP2);
	pointsDisplayPlayer2GameObject.get()->AddComponent(pointsComponent2);
	pointsDisplayPlayer2GameObject.get()->AddComponent(pointsDisplayComponent2);
	pointsDisplayPlayer2GameObject.get()->SetPosition(625, 10);
	scene.Add(pointsDisplayPlayer2GameObject);



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
	//player2 inputs
	InputManager::GetInstance().AddControllerCommandBinding<HitCommand>(ControllerButton::ButtonX, peterPeperGameObject2.get(), 1);
	InputManager::GetInstance().AddControllerCommandBinding<PointsCommand>(ControllerButton::ButtonY, pointsDisplayPlayer2GameObject.get(), 1);

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

void BurgerTimeGame::CreateLevel(Scene& scene) const
{
	CreateLadder(scene, 55, 90, "Ladder.png", "LadderDown");
	CreateLadder(scene, 55, 145, "Ladder.png", "LadderUp");
	CreateLadder(scene, 55, 310, "Ladder.png", "LadderDown");
	CreateLadder(scene, 55, 365, "Ladder.png");
	CreateLadder(scene, 55, 420, "Ladder.png", "LadderUp");
	CreateLadder(scene, 55, 475, "Ladder.png", "LadderDown");
	CreateLadder(scene, 55, 530, "Ladder.png", "LadderUp");
	//
	CreateLadder(scene, 135, 200, "Ladder.png", "LadderDown");
	CreateLadder(scene, 135, 255, "Ladder.png", "LadderUp");
	CreateLadder(scene, 135, 310, "Ladder.png", "LadderDown");
	CreateLadder(scene, 135, 365, "Ladder.png");
	CreateLadder(scene, 135, 420, "Ladder.png", "LadderUp");
	//
	CreateLadder(scene, 215, 90, "Ladder.png", "LadderDown");
	CreateLadder(scene, 215, 145, "Ladder.png", "LadderUp");
	CreateLadder(scene, 215, 200, "Ladder.png");
	CreateLadder(scene, 215, 255, "Ladder.png");
	CreateLadder(scene, 215, 310, "Ladder.png");
	CreateLadder(scene, 215, 365, "Ladder.png", "LadderDown");
	CreateLadder(scene, 215, 420, "Ladder.png","LadderUp");
	CreateLadder(scene, 215, 475, "Ladder.png", "LadderDown");
	CreateLadder(scene, 215, 530, "Ladder.png", "LadderUp");
	//
	CreateLadder(scene, 295, 90, "Ladder.png", "LadderDown");
	CreateLadder(scene, 295, 145, "Ladder.png");
	CreateLadder(scene, 295, 200, "Ladder.png", "LadderUp");
	//
	CreateLadder(scene, 375, 90, "Ladder.png", "LadderDown");
	CreateLadder(scene, 375, 145, "Ladder.png", "LadderUp");
	CreateLadder(scene, 375, 200, "Ladder.png");
	CreateLadder(scene, 375, 255, "Ladder.png", "LadderDown");
	CreateLadder(scene, 375, 310, "Ladder.png", "LadderUp");
	CreateLadder(scene, 375, 365, "Ladder.png", "LadderDown");
	CreateLadder(scene, 375, 420, "Ladder.png", "LadderUp");
	CreateLadder(scene, 375, 475, "Ladder.png", "LadderDown");
	CreateLadder(scene, 375, 530, "Ladder.png","LadderUp");
	//
	CreateLadder(scene, 455, 200, "Ladder.png", "LadderDown");
	CreateLadder(scene, 455, 255, "Ladder.png");
	CreateLadder(scene, 455, 310, "Ladder.png", "LadderUp");
	//
	CreateLadder(scene, 535, 90,  "Ladder.png", "LadderDown");
	CreateLadder(scene, 535, 145, "Ladder.png", "LadderUp");
	CreateLadder(scene, 535, 200, "Ladder.png", "LadderDown");
	CreateLadder(scene, 535, 255, "Ladder.png", "LadderUp");
	CreateLadder(scene, 535, 310, "Ladder.png");
	CreateLadder(scene, 535, 365, "Ladder.png");
	CreateLadder(scene, 535, 420, "Ladder.png");
	CreateLadder(scene, 535, 475, "Ladder.png", "LadderDown");
	CreateLadder(scene, 535, 530, "Ladder.png","LadderUp");
	//
	CreateLadder(scene, 615, 310, "Ladder.png", "LadderDown");
	CreateLadder(scene, 615, 365, "Ladder.png", "LadderUp");
	CreateLadder(scene, 615, 420, "Ladder.png", "LadderDown");
	CreateLadder(scene, 615, 475, "Ladder.png");
	CreateLadder(scene, 615, 530, "Ladder.png", "LadderUp");
	//
	CreateLadder(scene, 695, 90, "Ladder.png", "LadderDown");
	CreateLadder(scene, 695, 145, "Ladder.png", "LadderUp");
	CreateLadder(scene, 695, 200, "Ladder.png", "LadderDown");
	CreateLadder(scene, 695, 255, "Ladder.png", "LadderUp");
	CreateLadder(scene, 695, 420, "Ladder.png", "LadderDown");
	CreateLadder(scene, 695, 475, "Ladder.png");
	CreateLadder(scene, 695, 530, "Ladder.png", "LadderUp");
	//


	CreatePlatform(scene, 55, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 95, 90, "BluePlatform.png");
	CreatePlatform(scene, 135, 90, "BluePlatform.png");
	CreatePlatform(scene, 175, 90, "BluePlatform.png");
	CreatePlatform(scene, 215, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 255, 90, "BluePlatform.png");
	CreatePlatform(scene, 295, 90, "BluePlatform.png");
	CreatePlatform(scene, 335, 90, "BluePlatform.png");
	CreatePlatform(scene, 375, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 415, 90, "BluePlatform.png");
	CreatePlatform(scene, 455, 90, "BluePlatform.png");
	CreatePlatform(scene, 495, 90, "BluePlatform.png");
	CreatePlatform(scene, 535, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 575, 90, "BluePlatform.png");
	CreatePlatform(scene, 615, 90, "BluePlatform.png");
	CreatePlatform(scene, 655, 90, "BluePlatform.png");
	CreatePlatform(scene, 695, 90, "LightBluePlatform.png");
	//
	CreatePlatform(scene, 55, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 95, 200, "BluePlatform.png");
	CreatePlatform(scene, 135, 200, "BluePlatform.png");
	CreatePlatform(scene, 175, 200, "BluePlatform.png");
	CreatePlatform(scene, 215, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 375, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 415, 200, "BluePlatform.png");
	CreatePlatform(scene, 455, 200, "BluePlatform.png");
	CreatePlatform(scene, 495, 200, "BluePlatform.png");
	CreatePlatform(scene, 535, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 575, 200, "BluePlatform.png");
	CreatePlatform(scene, 615, 200, "BluePlatform.png");
	CreatePlatform(scene, 655, 200, "BluePlatform.png");
	CreatePlatform(scene, 695, 200, "LightBluePlatform.png");
	//
	CreatePlatform(scene, 215, 255, "LightBluePlatform.png");
	CreatePlatform(scene, 255, 255, "BluePlatform.png");
	CreatePlatform(scene, 295, 255, "BluePlatform.png");
	CreatePlatform(scene, 335, 255, "BluePlatform.png");
	CreatePlatform(scene, 375, 255, "LightBluePlatform.png");
	//
	CreatePlatform(scene, 55, 310, "LightBluePlatform.png");
	CreatePlatform(scene, 95, 310, "BluePlatform.png");
	CreatePlatform(scene, 135, 310, "BluePlatform.png");
	CreatePlatform(scene, 175, 310, "BluePlatform.png");
	CreatePlatform(scene, 215, 310, "LightBluePlatform.png");
	CreatePlatform(scene, 535, 310, "LightBluePlatform.png");
	CreatePlatform(scene, 575, 310, "BluePlatform.png");
	CreatePlatform(scene, 615, 310, "BluePlatform.png");
	CreatePlatform(scene, 655, 310, "BluePlatform.png");
	CreatePlatform(scene, 695, 310, "LightBluePlatform.png");
	//
	CreatePlatform(scene, 215, 365, "LightBluePlatform.png");
	CreatePlatform(scene, 255, 365, "BluePlatform.png");
	CreatePlatform(scene, 295, 365, "BluePlatform.png");
	CreatePlatform(scene, 335, 365, "BluePlatform.png");
	CreatePlatform(scene, 375, 365, "LightBluePlatform.png");
	CreatePlatform(scene, 415, 365, "BluePlatform.png");
	CreatePlatform(scene, 455, 365, "BluePlatform.png");
	CreatePlatform(scene, 495, 365, "BluePlatform.png");
	CreatePlatform(scene, 535, 365, "LightBluePlatform.png");
	//
	CreatePlatform(scene, 535, 420, "LightBluePlatform.png");
	CreatePlatform(scene, 575, 420, "BluePlatform.png");
	CreatePlatform(scene, 615, 420, "BluePlatform.png");
	CreatePlatform(scene, 655, 420, "BluePlatform.png");
	CreatePlatform(scene, 695, 420, "LightBluePlatform.png");
	//
	CreatePlatform(scene, 55, 475, "LightBluePlatform.png");
	CreatePlatform(scene, 95, 475, "BluePlatform.png");
	CreatePlatform(scene, 135, 475, "BluePlatform.png");
	CreatePlatform(scene, 175, 475, "BluePlatform.png");
	CreatePlatform(scene, 215, 475, "LightBluePlatform.png");
	CreatePlatform(scene, 255, 475, "BluePlatform.png");
	CreatePlatform(scene, 295, 475, "BluePlatform.png");
	CreatePlatform(scene, 335, 475, "BluePlatform.png");
	CreatePlatform(scene, 375, 475, "LightBluePlatform.png");
	CreatePlatform(scene, 415, 475, "BluePlatform.png");
	CreatePlatform(scene, 455, 475, "BluePlatform.png");
	CreatePlatform(scene, 495, 475, "BluePlatform.png");
	CreatePlatform(scene, 535, 475, "LightBluePlatform.png");
	//
	CreatePlatform(scene, 55, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 95, 585, "BluePlatform.png");
	CreatePlatform(scene, 135, 585, "BluePlatform.png");
	CreatePlatform(scene, 175, 585, "BluePlatform.png");
	CreatePlatform(scene, 215, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 255, 585, "BluePlatform.png");
	CreatePlatform(scene, 295, 585, "BluePlatform.png");
	CreatePlatform(scene, 335, 585, "BluePlatform.png");
	CreatePlatform(scene, 375, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 415, 585, "BluePlatform.png");
	CreatePlatform(scene, 455, 585, "BluePlatform.png");
	CreatePlatform(scene, 495, 585, "BluePlatform.png");
	CreatePlatform(scene, 535, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 575, 585, "BluePlatform.png");
	CreatePlatform(scene, 615, 585, "BluePlatform.png");
	CreatePlatform(scene, 655, 585, "BluePlatform.png");
	CreatePlatform(scene, 695, 585, "LightBluePlatform.png");


	//Borders
	CreateBorder(scene, 55, 62, 651.5f, "TopBorder");
}

void BurgerTimeGame::CreatePlatform(Scene& scene, float x, float y,const std::string& texture) const
{
	auto platformObject = std::make_shared<GameObject>();
	platformObject.get()->SetTag("Platform");
	auto pPlatformTexture = ResourceManager::GetInstance().LoadTexture(texture);
	auto spriteRenderComp = std::make_shared<RenderComponent>(platformObject.get(), pPlatformTexture);
	platformObject.get()->AddComponent(spriteRenderComp);
	BoundingBox collisionBox{ spriteRenderComp.get()->GetWidth(), spriteRenderComp.get()->GetHeight() };
	platformObject.get()->AddComponent(std::make_unique<CollisionComponent>(platformObject.get(), collisionBox));
	platformObject.get()->SetPosition(x, y);
	scene.Add(platformObject);
}

void BurgerTimeGame::CreateLadder(Scene& scene, float x, float y, const std::string& texture, const std::string& tag) const
{
	auto ladderObject = std::make_shared<GameObject>();
	ladderObject.get()->SetTag(tag);
	auto pLadderTexture = ResourceManager::GetInstance().LoadTexture(texture);
	auto spriteRenderComp = std::make_shared<RenderComponent>(ladderObject.get(), pLadderTexture);
	ladderObject.get()->AddComponent(spriteRenderComp);
	BoundingBox collisionBox{ spriteRenderComp.get()->GetWidth(), spriteRenderComp.get()->GetHeight() };
	ladderObject.get()->AddComponent(std::make_unique<CollisionComponent>(ladderObject.get(), collisionBox));
	ladderObject.get()->SetPosition(x, y);
	scene.Add(ladderObject);
}

void BurgerTimeGame::CreateBorder(dae::Scene& scene, float x, float y, float width, const std::string& tag) const
{
	auto border = std::make_shared<GameObject>();
	border.get()->SetTag(tag);
	BoundingBox collisionBox{ width, 1.0f };
	border.get()->AddComponent(std::make_shared<RenderComponent>(border.get(), nullptr));
	border.get()->AddComponent(std::make_unique<CollisionComponent>(border.get(), collisionBox));
	border.get()->SetPosition(x, y);
	scene.Add(border);
}
