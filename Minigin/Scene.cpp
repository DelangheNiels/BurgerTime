#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "CollisionComponent.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

void dae::Scene::LoadScene()
{
}

Scene::Scene(const std::string& name) : m_Name(name)
{
}

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
}

void dae::Scene::FixedUpdate(float fixedTime)
{
	HandleCollisions();

	for (auto& object : m_Objects)
	{
		object.get()->FixedUpdate(fixedTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		auto renderComp = object.get()->GetComponent<RenderComponent>();
		if(renderComp)
			renderComp->Render();
		
	}
}

void dae::Scene::HandleCollisions()
{
	std::vector<CollisionComponent*> collisionComponents;
	for (const auto& gameObject : m_Objects)
	{
		auto collisionComp = gameObject.get()->GetComponent<CollisionComponent>();
		if (collisionComp)
		{
			collisionComponents.push_back(collisionComp);
		}
	}

	for (size_t i=0; i< collisionComponents.size(); ++i)
	{
		for (size_t j = 0; j < collisionComponents.size(); ++j)
		{
			if (collisionComponents[i] != collisionComponents[j])
			{
				collisionComponents[i]->CheckCollision(collisionComponents[j]->GetBoundingBox(), collisionComponents[j]->GetGameObject());

			}
		}
	}
}
