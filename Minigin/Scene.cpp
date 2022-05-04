#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "../BurgerTime/GroundCheckComponent.h"
#include "../BurgerTime/PlatformComponent.h"
#include "../BurgerTime/PeterPeperComponent.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object.get()->Update(deltaTime);
	}

	HandleCollisions();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		auto renderComp = object.get()->GetComponent<RenderComponent>();
		renderComp->Render();
		
	}
}

void dae::Scene::HandleCollisions()
{
	for (const auto& object : m_Objects)
	{
		auto groundComponent = object.get()->GetComponent<GroundCheckComponent>();
		if (groundComponent != nullptr)
		{
			for (const auto& object2 : m_Objects)
			{
				if (object2.get()->GetComponent<PlatformComponent>() != nullptr)
				{
					if (groundComponent->CheckOnGround(object2.get()))
					{
						object.get()->GetComponent<PeterPeperComponent>()->SetOnGround(true);
					}
				}
			}
			
		}

	}
}

