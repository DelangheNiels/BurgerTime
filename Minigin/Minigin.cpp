#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "PeterPeperComponent.h"
#include "PlayerHealthDisplayComponent.h"
#include "PointsComponent.h"
#include "PointsDisplayComponent.h"
#include "Command.h"
//#include <steam_api.h>
//#include "PointsAchievementObserver.h"


using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		900,
		780,
		SDL_WINDOW_OPENGL
		//640, 480
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	Renderer::GetInstance().Init(m_Window);

	
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//background
	/*auto screenGameObject = std::make_shared<GameObject>();
	auto  pBackgroundTexture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	screenGameObject.get()->AddComponent(std::make_shared<RenderComponent>(screenGameObject.get(), pBackgroundTexture));
	scene.Add(screenGameObject);*/

	////logo
	//auto logoGameObject = std::make_shared<GameObject>();
	//logoGameObject.get()->AddComponent(std::make_shared<RenderComponent>(logoGameObject.get(), ResourceManager::GetInstance().LoadTexture("logo.png")));
	//logoGameObject.get()->SetPosition(216, 180);
	//scene.Add(logoGameObject);

	////title
	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto titleGameObject = std::make_shared<GameObject>();
	//auto titleRenderComp = std::make_shared<RenderComponent>(titleGameObject.get(), nullptr);
	//titleGameObject.get()->AddComponent(titleRenderComp);
	//titleGameObject.get()->AddComponent(std::make_shared<TextComponent>(titleGameObject.get(), "Programming 4 Assignment", font, titleRenderComp));
	//titleGameObject.get()->SetPosition(80, 20);
	//scene.Add(titleGameObject);

	//Level background
	auto screenGameObject = std::make_shared<GameObject>();
	auto  pBackgroundTexture = ResourceManager::GetInstance().LoadTexture("Level.png");
	screenGameObject.get()->AddComponent(std::make_shared<RenderComponent>(screenGameObject.get(), pBackgroundTexture));
	scene.Add(screenGameObject);

	//fps counter
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto fpsGameObject = std::make_shared<GameObject>();
	const SDL_Color color = { 255,255,0 };
	auto renderComp = std::make_shared<RenderComponent>(fpsGameObject.get(), nullptr);
	auto textComp = std::make_shared<TextComponent>(fpsGameObject.get(), "FPS: 0", font, renderComp,color);
	fpsGameObject.get()->AddComponent(renderComp);
	fpsGameObject.get()->AddComponent(textComp);
	fpsGameObject.get()->AddComponent(std::make_shared<FPSComponent>(fpsGameObject.get(), textComp));
	fpsGameObject.get()->SetPosition(2, 10);
	scene.Add(fpsGameObject);


	//Achievements
	//auto achievementsGameObject = std::make_shared<GameObject>();
	////auto pointsAchievementObserver = std::make_shared<PointsAchievementObserver>(achievementsGameObject.get(), m_AchievementSystem.GetSteamAchievements());
	////achievementsGameObject.get()->AddComponent(pointsAchievementObserver);
	//auto renderCompAchievements = std::make_shared<RenderComponent>(achievementsGameObject.get(), nullptr);
	//achievementsGameObject.get()->AddComponent(renderCompAchievements);
	//scene.Add(achievementsGameObject);

	//PeterPeper GameObject
	auto peterPeperGameObject = std::make_shared<GameObject>();
	auto playerOne = std::make_shared<PeterPeperComponent>(peterPeperGameObject.get(), 3);
	auto spriteRenderComp = std::make_shared<RenderComponent>(peterPeperGameObject.get(), ResourceManager::GetInstance().LoadTexture("PlayerIdle.png"));
	peterPeperGameObject.get()->AddComponent(playerOne);
	peterPeperGameObject.get()->AddComponent(spriteRenderComp);
	peterPeperGameObject.get()->SetPosition(200, 200);
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
	InputManager::GetInstance().AddControllerCommandBinding<HitCommand>(ControllerButton::ButtonA , peterPeperGameObject.get(), 0);
	InputManager::GetInstance().AddControllerCommandBinding<PointsCommand>(ControllerButton::ButtonB, pointsDisplayPlayerOneGameObject.get(), 0);
	InputManager::GetInstance().AddControllerCommandBinding<MoveLeftCommand>(ControllerButton::ButtonLeft, peterPeperGameObject.get(), 0);
	InputManager::GetInstance().AddControllerCommandBinding<MoveRightCommand>(ControllerButton::ButtonRight, peterPeperGameObject.get(), 0);
	//player2 inputs
	InputManager::GetInstance().AddControllerCommandBinding<HitCommand>(ControllerButton::ButtonX, peterPeperGameObject2.get(), 1);
	InputManager::GetInstance().AddControllerCommandBinding<PointsCommand>(ControllerButton::ButtonY, pointsDisplayPlayer2GameObject.get(), 1);
	
	std::cout << "Used controlls:" << "\n";
	std::cout << "======================" << "\n";
	std::cout << "Player1:" << "\n";
	std::cout << "Damage: A" << "\n";
	std::cout << "Points: B" << "\n";
	std::cout << "======================" << "\n";
	std::cout << "Player2:" << "\n";
	std::cout << "Damage: X" << "\n";
	std::cout << "Points: Y" << "\n";
	std::cout << "======================" << "\n";
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		// todo: this update loop could use some work.
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;
		while (doContinue)
		{

			//SteamAPI_RunCallbacks();

			const auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;

			doContinue = input.ProcessInput();
			while (lag >= m_FixedTimeStep)
			{
				sceneManager.FixedUpdate(m_FixedTimeStep);
				lag -= m_FixedTimeStep;
			}

			sceneManager.Update(deltaTime);
			renderer.Render();
			//renderer.RenderImGui();

			//cap fps
			const auto sleepTime = currentTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now();
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
