#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "CollisionComponent.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;



Scene::Scene(const std::string& name) : m_Name(name)
{
	m_IsActive = false;
}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	if (m_IsActive)
	{
		for (auto& object : m_Objects)
		{
			object.get()->Update(deltaTime);
		}
	}
	
}

void dae::Scene::FixedUpdate(float fixedTime)
{
	if (m_IsActive)
	{
		HandleCollisions();

		for (auto& object : m_Objects)
		{
			object.get()->FixedUpdate(fixedTime);
		}
	}
	
}

void Scene::Render() const
{
	if (m_IsActive)
	{
		for (const auto& object : m_Objects)
		{
			auto renderComp = object.get()->GetComponent<RenderComponent>();
			if (renderComp)
				renderComp->Render();

		}
	}
	
}

void dae::Scene::SetActive()
{
	m_IsActive = true;
}

void dae::Scene::SetInActive()
{
	m_IsActive = false;
}

bool dae::Scene::GetIsActive()
{
	return m_IsActive;
}

std::string dae::Scene::GetSceneName() const
{
	return m_Name;
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
