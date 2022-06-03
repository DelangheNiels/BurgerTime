#include "BurgerTimePCH.h"
#include "LevelLoader.h"

#include <fstream>

#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "CollisionComponent.h"

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
			float x, y, width;
			std::string tag;

			file >> x >> y >> width >> tag;

			auto border = std::make_shared<GameObject>();
			border.get()->SetTag(tag);
			BoundingBox collisionBox{ width, 1.0f };
			border.get()->AddComponent(std::make_unique<CollisionComponent>(border.get(), collisionBox));
			border.get()->SetPosition(x, y);
			scene.Add(border);
		}

		else
		{
			//Ignore the line
		}
	}

	file.close();
}
