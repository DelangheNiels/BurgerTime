#include "BurgerTimePCH.h"
#include "LevelLoader.h"

#include <fstream>

#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "AIMovementComponent.h"
#include "BurgerPartComponent.h"
#include "BurgerComponent.h"

dae::LevelLoader::LevelLoader(const std::string& filename)
{
	m_Inputfile = "../Data/TextFiles/" + filename;
}

void dae::LevelLoader::LoadLevel(Scene& scene)
{
	std::ifstream file(m_Inputfile);

	if (!file)
	{
		std::cout << "file not found" << "\n";
		return;
	}

	std::string indicator;

	while (!file.eof())
	{
		//read first word
		file >> indicator;

		if (indicator == "P")
		{
			float x, y;
			std::string texture;

			file >> x >> y >> texture;

			auto platformObject = std::make_shared<GameObject>();
			platformObject.get()->SetTag("Platform");
			auto pPlatformTexture = ResourceManager::GetInstance().LoadTexture(texture);
			auto spriteRenderComp = std::make_shared<dae::RenderComponent>(platformObject.get(), pPlatformTexture);
			platformObject.get()->AddComponent(spriteRenderComp);
			platformObject.get()->SetPosition(x, y);
			scene.Add(platformObject);
		}

		else if (indicator == "L")
		{
			float x, y;
			std::string texture, tag;

			file >> x >> y >> texture >> tag;

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

		else if (indicator == "B")
		{
			float x, y, width, height;
			std::string tag;

			file >> x >> y >> width >> height >>tag;

			auto border = std::make_shared<GameObject>();
			border.get()->SetTag(tag);
			BoundingBox collisionBox{ width, height };
			border.get()->AddComponent(std::make_unique<CollisionComponent>(border.get(), collisionBox));
			border.get()->SetPosition(x, y);
			scene.Add(border);
		}

		else if (indicator == "EH")
		{
			float x, y;

			file >> x >> y;

			auto hotdog = std::make_shared<GameObject>();
			hotdog.get()->SetTag("MrHotdog");
			auto hotdogSpriteRenderComp = std::make_shared<RenderComponent>(hotdog.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/PlayerSprites/Player2Idle.png"));
			BoundingBox hotdogCollisionBox{ hotdogSpriteRenderComp.get()->GetWidth(), hotdogSpriteRenderComp.get()->GetHeight() };
			auto hotdogCollisionComponent = std::make_shared<CollisionComponent>(hotdog.get(), hotdogCollisionBox);

			auto hotdogWalkLeft = std::make_shared<AnimatedSpriteComponent>(hotdog.get(), hotdogSpriteRenderComp.get(), 2, ResourceManager::GetInstance().LoadSpriteSheet("MrHotdogSprites/WalkingLeft.png"));
			auto hotdogWalkRight = std::make_shared<AnimatedSpriteComponent>(hotdog.get(), hotdogSpriteRenderComp.get(), 2, ResourceManager::GetInstance().LoadSpriteSheet("MrHotdogSprites/WalkingRight.png"));
			auto hotdogWalkUp = std::make_shared<AnimatedSpriteComponent>(hotdog.get(), hotdogSpriteRenderComp.get(), 2, ResourceManager::GetInstance().LoadSpriteSheet("MrHotdogSprites/WalkingUp.png"));
			auto hotdogWalkDown = std::make_shared<AnimatedSpriteComponent>(hotdog.get(), hotdogSpriteRenderComp.get(), 2, ResourceManager::GetInstance().LoadSpriteSheet("MrHotdogSprites/WalkingDown.png"));
			auto hotdogDead = std::make_shared<AnimatedSpriteComponent>(hotdog.get(), hotdogSpriteRenderComp.get(), 4, ResourceManager::GetInstance().LoadSpriteSheet("MrHotdogSprites/Dying.png"));
			std::map<EnemyState, AnimatedSpriteComponent*> hotdogAnimations;

			hotdogAnimations.insert(std::pair<EnemyState, AnimatedSpriteComponent*>(EnemyState::WalkingLeft, hotdogWalkLeft.get()));
			hotdogAnimations.insert(std::pair<EnemyState, AnimatedSpriteComponent*>(EnemyState::WalkingRight, hotdogWalkRight.get()));
			hotdogAnimations.insert(std::pair<EnemyState, AnimatedSpriteComponent*>(EnemyState::WalkingUp, hotdogWalkUp.get()));
			hotdogAnimations.insert(std::pair<EnemyState, AnimatedSpriteComponent*>(EnemyState::WalkingDown, hotdogWalkDown.get()));
			hotdogAnimations.insert(std::pair<EnemyState, AnimatedSpriteComponent*>(EnemyState::Dying, hotdogDead.get()));

			auto hotdogComp = std::make_shared<EnemyComponent>(hotdog.get(), hotdogSpriteRenderComp.get(), hotdogAnimations, x, y);
			auto AIMovementComp = std::make_shared<AIMovementComponent>(hotdog.get(), hotdogComp.get());
			hotdog.get()->AddComponent(hotdogComp);
			hotdog.get()->AddComponent(AIMovementComp);
			hotdog.get()->AddComponent(hotdogSpriteRenderComp);
			hotdog.get()->AddComponent(hotdogCollisionComponent);
			hotdog.get()->AddComponent(hotdogWalkLeft);
			hotdog.get()->AddComponent(hotdogWalkDown);
			hotdog.get()->AddComponent(hotdogWalkRight);
			hotdog.get()->AddComponent(hotdogWalkUp);
			hotdog.get()->AddComponent(hotdogDead);
			scene.Add(hotdog);
		}

		else if (indicator == "C")
		{
			float x{}, y{}, borderW{}, borderH{}, borderX{}, borderY{};

			file >> x >> y >> borderW >> borderH >> borderX >> borderY;

			auto catcherObj = std::make_shared<GameObject>();
			auto renderCompCatcher = std::make_shared<RenderComponent>(catcherObj.get(), ResourceManager::GetInstance().LoadTexture("SpriteSheets/BurgerSprites/Catcher.png"));
			catcherObj.get()->AddComponent(renderCompCatcher);
			catcherObj.get()->SetPosition(x, y);
			scene.Add(catcherObj);
			auto catcherObjBorder = std::make_shared<GameObject>();
			catcherObjBorder.get()->SetTag("Catcher");
			BoundingBox collisionBoxCatcher{ borderW, borderH };
			catcherObjBorder.get()->AddComponent(std::make_unique<CollisionComponent>(catcherObjBorder.get(), collisionBoxCatcher));
			catcherObjBorder.get()->SetPosition(borderX, borderY);
			scene.Add(catcherObjBorder);
		}

		else
		{
			//Ignore the line
		}
	}

	file.close();
}
