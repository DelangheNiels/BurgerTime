#include "BurgerTimePCH.h"
#include "GameSceneMultiplayer.h"

#include "LevelLoader.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Command.h"
#include "ServiceLocator.h"
#include "HighscoreManager.h"
#include "GameManager.h"

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

dae::GameSceneMultiplayer::GameSceneMultiplayer(const std::string& name)
	:Scene(name)
{
	//LoadScene();
}

void dae::GameSceneMultiplayer::LoadScene()
{
	if (!m_IsLoaded)
	{
		//Load level
		LevelLoader loader = LevelLoader("Level.txt");
		loader.LoadLevel(*this);
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
		Add(fpsGameObject);

		//HighScore
		auto highScoreObject = std::make_shared<GameObject>();
		auto highscoreFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
		auto highscoreRenderComp = std::make_shared<RenderComponent>(highScoreObject.get(), nullptr);
		std::string highscoreText = "Highscore: " + std::to_string(HighscoreManager::GetInstance().GetHighScore());
		auto highscoreTextComp = std::make_shared<TextComponent>(highScoreObject.get(), highscoreText, highscoreFont, highscoreRenderComp, SDL_Color{ 255,255,255 });
		highScoreObject.get()->AddComponent(highscoreRenderComp);
		highScoreObject.get()->AddComponent(highscoreTextComp);
		highScoreObject.get()->SetPosition(550, 20);
		Add(highScoreObject);


		//PeterPeper GameObject
		auto peterPeperGameObject = std::make_shared<GameObject>();
		peterPeperGameObject.get()->SetTag("Player");

		auto spriteRenderComp = std::make_shared<RenderComponent>(peterPeperGameObject.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/PlayerSprites/PlayerIdle.png"));
		BoundingBox collisionBox{ spriteRenderComp.get()->GetWidth(), spriteRenderComp.get()->GetHeight() };
		auto collisionComponent = std::make_shared<CollisionComponent>(peterPeperGameObject.get(), collisionBox);

		auto idleAnimation = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject.get(), spriteRenderComp.get(), 1, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/PlayerIdle.png"));
		auto walkLeftAnimation = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject.get(), spriteRenderComp.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/PlayerWalkingLeft.png"));
		auto walkRightAnimation = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject.get(), spriteRenderComp.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/PlayerWalkingRight.png"));
		auto walkUpAnimation = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject.get(), spriteRenderComp.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/PlayerWalkingUp.png"));
		auto walkDownAnimation = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject.get(), spriteRenderComp.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/PlayerWalkingDown.png"));
		auto dyingAnimation = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject.get(), spriteRenderComp.get(), 6, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/PlayerDying.png"));
		std::map<PlayerStates, AnimatedSpriteComponent*> animations;

		animations.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::Idle, idleAnimation.get()));
		animations.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::WalkingLeft, walkLeftAnimation.get()));
		animations.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::WalkingRight, walkRightAnimation.get()));
		animations.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::ClimbingUp, walkUpAnimation.get()));
		animations.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::ClimbingDown, walkDownAnimation.get()));
		animations.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::Dying, dyingAnimation.get()));

		auto playerOne = std::make_shared<PeterPeperComponent>(peterPeperGameObject.get(), 3, spriteRenderComp.get(), animations, 375.0f, 563.0f);
		GameManager::GetInstance().AddPlayer(playerOne.get());
		peterPeperGameObject.get()->AddComponent(playerOne);
		peterPeperGameObject.get()->AddComponent(spriteRenderComp);
		peterPeperGameObject.get()->AddComponent(collisionComponent);
		peterPeperGameObject.get()->AddComponent(idleAnimation);
		peterPeperGameObject.get()->AddComponent(walkLeftAnimation);
		peterPeperGameObject.get()->AddComponent(walkRightAnimation);
		peterPeperGameObject.get()->AddComponent(walkUpAnimation);
		peterPeperGameObject.get()->AddComponent(walkDownAnimation);
		peterPeperGameObject.get()->AddComponent(dyingAnimation);
		Add(peterPeperGameObject);

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
		Add(playerOneHealthDisplayObject);

		//points display player one
		auto pointsDisplayPlayerOneGameObject = std::make_shared<GameObject>();
		auto renderCompPointsP1 = std::make_shared<RenderComponent>(pointsDisplayPlayerOneGameObject.get(), nullptr);
		auto textCompPointsP1 = std::make_shared<TextComponent>(pointsDisplayPlayerOneGameObject.get(), "", font, renderCompPointsP1, colorP1);

		auto pointsComponent = std::make_shared<PointsComponent>(pointsDisplayPlayerOneGameObject.get());
		auto pointsDisplayComponent = std::make_shared<PointsDisplayComponent>(pointsDisplayPlayerOneGameObject.get(), textCompPointsP1);
		pointsComponent.get()->AddPointsObserver(pointsDisplayComponent.get());

		auto pointsComponent2 = std::make_shared<PointsComponent>(pointsDisplayPlayerOneGameObject.get());
		pointsComponent2.get()->AddPointsObserver(pointsDisplayComponent.get());

		pointsDisplayPlayerOneGameObject.get()->AddComponent(renderCompPointsP1);
		pointsDisplayPlayerOneGameObject.get()->AddComponent(textCompPointsP1);
		pointsDisplayPlayerOneGameObject.get()->AddComponent(pointsComponent);
		pointsDisplayPlayerOneGameObject.get()->AddComponent(pointsComponent2);
		pointsDisplayPlayerOneGameObject.get()->AddComponent(pointsDisplayComponent);
		pointsDisplayPlayerOneGameObject.get()->SetPosition(225, 10);
		Add(pointsDisplayPlayerOneGameObject);


		/////////////////////////////////////////////////////////////////////////
		// 

		//Player2
		auto peterPeperGameObject2 = std::make_shared<GameObject>();
		peterPeperGameObject2.get()->SetTag("Player");
		auto spriteRenderComp2 = std::make_shared<RenderComponent>(peterPeperGameObject2.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/PlayerSprites/Player2Idle.png"));
		BoundingBox collisionBox2{ spriteRenderComp2.get()->GetWidth(), spriteRenderComp2.get()->GetHeight() };
		auto collisionComponent2 = std::make_shared<CollisionComponent>(peterPeperGameObject2.get(), collisionBox2);

		auto idleAnimation2 = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject2.get(), spriteRenderComp2.get(), 1, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/Player2Idle.png"));
		auto walkLeftAnimation2 = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject2.get(), spriteRenderComp2.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/Player2WalkingLeft.png"));
		auto walkRightAnimation2 = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject2.get(), spriteRenderComp2.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/Player2WalkingRight.png"));
		auto walkUpAnimation2 = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject2.get(), spriteRenderComp2.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/Player2WalkingUp.png"));
		auto walkDownAnimation2 = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject2.get(), spriteRenderComp2.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/Player2WalkingDown.png"));
		auto deadAnimation2 = std::make_shared<AnimatedSpriteComponent>(peterPeperGameObject2.get(), spriteRenderComp2.get(), 3, ResourceManager::GetInstance().LoadSpriteSheet("PlayerSprites/Player2Dying.png"));
		std::map<PlayerStates, AnimatedSpriteComponent*> animations2;

		animations2.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::Idle, idleAnimation2.get()));
		animations2.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::WalkingLeft, walkLeftAnimation2.get()));
		animations2.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::WalkingRight, walkRightAnimation2.get()));
		animations2.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::ClimbingUp, walkUpAnimation2.get()));
		animations2.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::ClimbingDown, walkDownAnimation2.get()));
		animations2.insert(std::pair<PlayerStates, AnimatedSpriteComponent*>(PlayerStates::Dying, deadAnimation2.get()));

		auto player2 = std::make_shared<PeterPeperComponent>(peterPeperGameObject2.get(), 3, spriteRenderComp2.get(), animations2, 425.0f, 563.0f);
		GameManager::GetInstance().AddPlayer(player2.get());
		peterPeperGameObject2.get()->AddComponent(player2);
		peterPeperGameObject2.get()->AddComponent(spriteRenderComp2);
		peterPeperGameObject2.get()->AddComponent(collisionComponent2);
		peterPeperGameObject2.get()->AddComponent(idleAnimation2);
		peterPeperGameObject2.get()->AddComponent(walkLeftAnimation2);
		peterPeperGameObject2.get()->AddComponent(walkRightAnimation2);
		peterPeperGameObject2.get()->AddComponent(walkUpAnimation2);
		peterPeperGameObject2.get()->AddComponent(walkDownAnimation2);
		peterPeperGameObject2.get()->AddComponent(deadAnimation2);
		Add(peterPeperGameObject2);
		//peterPeperGameObject2.get()->SetPosition(95, 61);

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
		Add(player2HealthDisplayObject);

		//input commands
		InputManager::GetInstance().AddController(new XBox360Controller{ 0 });
		InputManager::GetInstance().AddController(new XBox360Controller{ 1 });

		//player 1 inputs
		InputManager::GetInstance().AddControllerCommandBinding<HitCommand>(ControllerButton::ButtonA, peterPeperGameObject.get(), 0);
		InputManager::GetInstance().AddControllerCommandBinding<MoveLeftCommand>(ControllerButton::ButtonLeft, peterPeperGameObject.get(), 0);
		InputManager::GetInstance().AddControllerCommandBinding<MoveRightCommand>(ControllerButton::ButtonRight, peterPeperGameObject.get(), 0);
		InputManager::GetInstance().AddControllerCommandBinding<MoveUpCommand>(ControllerButton::ButtonUp, peterPeperGameObject.get(), 0);
		InputManager::GetInstance().AddControllerCommandBinding<MoveDownCommand>(ControllerButton::ButtonDown, peterPeperGameObject.get(), 0);

		////player2 inputs
		InputManager::GetInstance().AddControllerCommandBinding<HitCommand>(ControllerButton::ButtonA, peterPeperGameObject2.get(), 1);
		InputManager::GetInstance().AddControllerCommandBinding<MoveLeftCommand>(ControllerButton::ButtonLeft, peterPeperGameObject2.get(), 1);
		InputManager::GetInstance().AddControllerCommandBinding<MoveRightCommand>(ControllerButton::ButtonRight, peterPeperGameObject2.get(), 1);
		InputManager::GetInstance().AddControllerCommandBinding<MoveUpCommand>(ControllerButton::ButtonUp, peterPeperGameObject2.get(), 1);
		InputManager::GetInstance().AddControllerCommandBinding<MoveDownCommand>(ControllerButton::ButtonDown, peterPeperGameObject2.get(), 1);

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

		//burgerPart
		auto burgerpartObject = std::make_shared<GameObject>();
		burgerpartObject.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp = std::make_shared<RenderComponent>(burgerpartObject.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BunTopP1.png"));
		BoundingBox burgercollisionBox{ burgerspriteRenderComp.get()->GetWidth(), burgerspriteRenderComp.get()->GetHeight() };
		auto burgercollisionComponent = std::make_shared<CollisionComponent>(burgerpartObject.get(), burgercollisionBox);
		auto burgerPartComp = std::make_shared<BurgerPartComponent>(burgerpartObject.get());
		burgerpartObject.get()->AddComponent(burgerspriteRenderComp);
		burgerpartObject.get()->AddComponent(burgercollisionComponent);
		burgerpartObject.get()->AddComponent(burgerPartComp);
		burgerpartObject.get()->SetPosition(110, 69);
		Add(burgerpartObject);

		auto burgerpartObject2 = std::make_shared<GameObject>();
		burgerpartObject2.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp2 = std::make_shared<RenderComponent>(burgerpartObject2.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BunTopP2.png"));
		BoundingBox burgercollisionBox2{ burgerspriteRenderComp2.get()->GetWidth(), burgerspriteRenderComp2.get()->GetHeight() };
		auto burgercollisionComponent2 = std::make_shared<CollisionComponent>(burgerpartObject2.get(), burgercollisionBox2);
		auto burgerPartComp2 = std::make_shared<BurgerPartComponent>(burgerpartObject2.get());
		burgerpartObject2.get()->AddComponent(burgerspriteRenderComp2);
		burgerpartObject2.get()->AddComponent(burgercollisionComponent2);
		burgerpartObject2.get()->AddComponent(burgerPartComp2);
		burgerpartObject2.get()->SetPosition(133, 69);
		Add(burgerpartObject2);

		auto burgerpartObject3 = std::make_shared<GameObject>();
		burgerpartObject3.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp3 = std::make_shared<RenderComponent>(burgerpartObject3.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BunTopP3.png"));
		BoundingBox burgercollisionBox3{ burgerspriteRenderComp3.get()->GetWidth(), burgerspriteRenderComp3.get()->GetHeight() };
		auto burgercollisionComponent3 = std::make_shared<CollisionComponent>(burgerpartObject3.get(), burgercollisionBox3);
		auto burgerPartComp3 = std::make_shared<BurgerPartComponent>(burgerpartObject3.get());
		burgerpartObject3.get()->AddComponent(burgerspriteRenderComp3);
		burgerpartObject3.get()->AddComponent(burgercollisionComponent3);
		burgerpartObject3.get()->AddComponent(burgerPartComp3);
		burgerpartObject3.get()->SetPosition(156, 69);
		Add(burgerpartObject3);

		auto burgerpartObject4 = std::make_shared<GameObject>();
		burgerpartObject4.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp4 = std::make_shared<RenderComponent>(burgerpartObject4.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BunTopP4.png"));
		BoundingBox burgercollisionBox4{ burgerspriteRenderComp4.get()->GetWidth(), burgerspriteRenderComp4.get()->GetHeight() };
		auto burgercollisionComponent4 = std::make_shared<CollisionComponent>(burgerpartObject4.get(), burgercollisionBox4);
		auto burgerPartComp4 = std::make_shared<BurgerPartComponent>(burgerpartObject4.get());
		burgerpartObject4.get()->AddComponent(burgerspriteRenderComp4);
		burgerpartObject4.get()->AddComponent(burgercollisionComponent4);
		burgerpartObject4.get()->AddComponent(burgerPartComp4);
		burgerpartObject4.get()->SetPosition(179, 69);
		Add(burgerpartObject4);


		//comp
		auto burgerObject = std::make_shared<GameObject>();
		auto burgerComp = std::make_shared<BurgerComponent>(burgerObject.get(), pointsComponent.get());

		burgerComp.get()->AddPart(burgerPartComp.get());
		burgerComp.get()->AddPart(burgerPartComp2.get());
		burgerComp.get()->AddPart(burgerPartComp3.get());
		burgerComp.get()->AddPart(burgerPartComp4.get());
		burgerObject.get()->AddComponent(burgerComp);

		Add(burgerObject);


		//secondpart

		auto burgerpartObject5 = std::make_shared<GameObject>();
		burgerpartObject5.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp5 = std::make_shared<RenderComponent>(burgerpartObject5.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BurgerP1.png"));
		BoundingBox burgercollisionBox5{ burgerspriteRenderComp5.get()->GetWidth(), burgerspriteRenderComp5.get()->GetHeight() };
		auto burgercollisionComponent5 = std::make_shared<CollisionComponent>(burgerpartObject5.get(), burgercollisionBox5);
		auto burgerPartComp5 = std::make_shared<BurgerPartComponent>(burgerpartObject5.get());
		burgerpartObject5.get()->AddComponent(burgerspriteRenderComp5);
		burgerpartObject5.get()->AddComponent(burgercollisionComponent5);
		burgerpartObject5.get()->AddComponent(burgerPartComp5);
		burgerpartObject5.get()->SetPosition(110, 180);
		Add(burgerpartObject5);

		auto burgerpartObject6 = std::make_shared<GameObject>();
		burgerpartObject6.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp6 = std::make_shared<RenderComponent>(burgerpartObject6.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BurgerP2.png"));
		BoundingBox burgercollisionBox6{ burgerspriteRenderComp6.get()->GetWidth(), burgerspriteRenderComp6.get()->GetHeight() };
		auto burgercollisionComponent6 = std::make_shared<CollisionComponent>(burgerpartObject6.get(), burgercollisionBox6);
		auto burgerPartComp6 = std::make_shared<BurgerPartComponent>(burgerpartObject6.get());
		burgerpartObject6.get()->AddComponent(burgerspriteRenderComp6);
		burgerpartObject6.get()->AddComponent(burgercollisionComponent6);
		burgerpartObject6.get()->AddComponent(burgerPartComp6);
		burgerpartObject6.get()->SetPosition(133, 180);
		Add(burgerpartObject6);

		auto burgerpartObject7 = std::make_shared<GameObject>();
		burgerpartObject7.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp7 = std::make_shared<RenderComponent>(burgerpartObject7.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BurgerP3.png"));
		BoundingBox burgercollisionBox7{ burgerspriteRenderComp7.get()->GetWidth(), burgerspriteRenderComp7.get()->GetHeight() };
		auto burgercollisionComponent7 = std::make_shared<CollisionComponent>(burgerpartObject7.get(), burgercollisionBox7);
		auto burgerPartComp7 = std::make_shared<BurgerPartComponent>(burgerpartObject7.get());
		burgerpartObject7.get()->AddComponent(burgerspriteRenderComp7);
		burgerpartObject7.get()->AddComponent(burgercollisionComponent7);
		burgerpartObject7.get()->AddComponent(burgerPartComp7);
		burgerpartObject7.get()->SetPosition(156, 180);
		Add(burgerpartObject7);

		auto burgerpartObject8 = std::make_shared<GameObject>();
		burgerpartObject8.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp8 = std::make_shared<RenderComponent>(burgerpartObject8.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BurgerP4.png"));
		BoundingBox burgercollisionBox8{ burgerspriteRenderComp8.get()->GetWidth(), burgerspriteRenderComp8.get()->GetHeight() };
		auto burgercollisionComponent8 = std::make_shared<CollisionComponent>(burgerpartObject8.get(), burgercollisionBox8);
		auto burgerPartComp8 = std::make_shared<BurgerPartComponent>(burgerpartObject8.get());
		burgerpartObject8.get()->AddComponent(burgerspriteRenderComp8);
		burgerpartObject8.get()->AddComponent(burgercollisionComponent8);
		burgerpartObject8.get()->AddComponent(burgerPartComp8);
		burgerpartObject8.get()->SetPosition(179, 180);
		Add(burgerpartObject8);


		//comp
		auto burgerObject2 = std::make_shared<GameObject>();
		auto burgerComp2 = std::make_shared<BurgerComponent>(burgerObject2.get(), pointsComponent2.get());

		burgerComp2.get()->AddPart(burgerPartComp5.get());
		burgerComp2.get()->AddPart(burgerPartComp6.get());
		burgerComp2.get()->AddPart(burgerPartComp7.get());
		burgerComp2.get()->AddPart(burgerPartComp8.get());
		burgerObject2.get()->AddComponent(burgerComp2);

		Add(burgerObject2);

		//3th part
		auto burgerpartObject9 = std::make_shared<GameObject>();
		burgerpartObject9.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp9 = std::make_shared<RenderComponent>(burgerpartObject9.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BunBottomP1.png"));
		BoundingBox burgercollisionBox9{ burgerspriteRenderComp9.get()->GetWidth(), burgerspriteRenderComp9.get()->GetHeight() };
		auto burgercollisionComponent9 = std::make_shared<CollisionComponent>(burgerpartObject9.get(), burgercollisionBox9);
		auto burgerPartComp9 = std::make_shared<BurgerPartComponent>(burgerpartObject9.get());
		burgerpartObject9.get()->AddComponent(burgerspriteRenderComp9);
		burgerpartObject9.get()->AddComponent(burgercollisionComponent9);
		burgerpartObject9.get()->AddComponent(burgerPartComp9);
		burgerpartObject9.get()->SetPosition(110, 290);
		Add(burgerpartObject9);

		auto burgerpartObject10 = std::make_shared<GameObject>();
		burgerpartObject10.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp10 = std::make_shared<RenderComponent>(burgerpartObject10.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BunBottomP2.png"));
		BoundingBox burgercollisionBox10{ burgerspriteRenderComp10.get()->GetWidth(), burgerspriteRenderComp10.get()->GetHeight() };
		auto burgercollisionComponent10 = std::make_shared<CollisionComponent>(burgerpartObject10.get(), burgercollisionBox10);
		auto burgerPartComp10 = std::make_shared<BurgerPartComponent>(burgerpartObject10.get());
		burgerpartObject10.get()->AddComponent(burgerspriteRenderComp10);
		burgerpartObject10.get()->AddComponent(burgercollisionComponent10);
		burgerpartObject10.get()->AddComponent(burgerPartComp10);
		burgerpartObject10.get()->SetPosition(133, 290);
		Add(burgerpartObject10);

		auto burgerpartObject11 = std::make_shared<GameObject>();
		burgerpartObject11.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp11 = std::make_shared<RenderComponent>(burgerpartObject11.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BunBottomP3.png"));
		BoundingBox burgercollisionBox11{ burgerspriteRenderComp11.get()->GetWidth(), burgerspriteRenderComp11.get()->GetHeight() };
		auto burgercollisionComponent11 = std::make_shared<CollisionComponent>(burgerpartObject11.get(), burgercollisionBox11);
		auto burgerPartComp11 = std::make_shared<BurgerPartComponent>(burgerpartObject11.get());
		burgerpartObject11.get()->AddComponent(burgerspriteRenderComp11);
		burgerpartObject11.get()->AddComponent(burgercollisionComponent11);
		burgerpartObject11.get()->AddComponent(burgerPartComp11);
		burgerpartObject11.get()->SetPosition(156, 290);
		Add(burgerpartObject11);

		auto burgerpartObject12 = std::make_shared<GameObject>();
		burgerpartObject12.get()->SetTag("BurgerPart");
		auto burgerspriteRenderComp12 = std::make_shared<RenderComponent>(burgerpartObject12.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/BunBottomP4.png"));
		BoundingBox burgercollisionBox12{ burgerspriteRenderComp12.get()->GetWidth(), burgerspriteRenderComp12.get()->GetHeight() };
		auto burgercollisionComponent12 = std::make_shared<CollisionComponent>(burgerpartObject12.get(), burgercollisionBox12);
		auto burgerPartComp12 = std::make_shared<BurgerPartComponent>(burgerpartObject12.get());
		burgerpartObject12.get()->AddComponent(burgerspriteRenderComp12);
		burgerpartObject12.get()->AddComponent(burgercollisionComponent12);
		burgerpartObject12.get()->AddComponent(burgerPartComp12);
		burgerpartObject12.get()->SetPosition(179, 290);
		Add(burgerpartObject12);

		//comp
		auto burgerObject3 = std::make_shared<GameObject>();
		auto burgerComp3 = std::make_shared<BurgerComponent>(burgerObject3.get(), pointsComponent2.get());
		burgerComp3.get()->AddPart(burgerPartComp9.get());
		burgerComp3.get()->AddPart(burgerPartComp10.get());
		burgerComp3.get()->AddPart(burgerPartComp11.get());
		burgerComp3.get()->AddPart(burgerPartComp12.get());
		burgerObject3.get()->AddComponent(burgerComp3);
		Add(burgerObject3);


		m_IsLoaded = true;
	}
	
}
