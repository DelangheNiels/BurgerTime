#include "BurgerTimePCH.h"
#include "MrHotdogComponent.h"

#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "AnimatedSpriteComponent.h"
#include "PeterPeperComponent.h"
#include "ResourceManager.h"

dae::MrHotdogComponent::MrHotdogComponent(GameObject* gameObject,RenderComponent* renderComp, std::map<EnemyState, AnimatedSpriteComponent*> animations)
	:Component(gameObject), m_pRenderComponent{renderComp}, m_Animations{animations}
{
	m_CurrentState = EnemyState::WalkingLeft;
	m_pCurrentAnimation = m_Animations.find(m_CurrentState)->second;
	m_pCurrentAnimation->Activate();
	m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture(m_pCurrentAnimation->GetSpriteSheet()));
}

void dae::MrHotdogComponent::Update(float deltaTime)
{
	m_pCurrentAnimation->Update(deltaTime);
}

void dae::MrHotdogComponent::FixedUpdate(float)
{
}

void dae::MrHotdogComponent::OnCollision(GameObject* pOther)
{
}

void dae::MrHotdogComponent::OnEndCollision(GameObject*)
{
}

float dae::MrHotdogComponent::GetPoints() const
{
	return m_Points;
}

dae::EnemyState dae::MrHotdogComponent::GetState() const
{
	return m_CurrentState;
}
