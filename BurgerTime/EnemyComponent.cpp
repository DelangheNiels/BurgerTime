#include "BurgerTimePCH.h"
#include "EnemyComponent.h"

#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "AnimatedSpriteComponent.h"
#include "PeterPeperComponent.h"
#include "ResourceManager.h"

dae::EnemyComponent::EnemyComponent(GameObject* gameObject, RenderComponent* renderComp, std::map<EnemyState, AnimatedSpriteComponent*> animations, float startPosX, float startPosY)
	:Component(gameObject), m_pRenderComponent{ renderComp }, m_Animations{ animations }, m_StartX{ startPosX }, m_StartY{ startPosY }
{
	m_pGameObject->SetPosition(m_StartX, m_StartY);
	m_CurrentState = EnemyState::WalkingLeft;
	m_pCurrentAnimation = m_Animations.find(m_CurrentState)->second;
	m_pCurrentAnimation->Activate();
	m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture(m_pCurrentAnimation->GetSpriteSheet()));
	m_PlayDeadTime = ((animations.find(EnemyState::Dying)->second->GetAmountOfAnimations() - 1) * (animations.find(EnemyState::Dying)->second->GetChangeImageTime())) / 2;
}

void dae::EnemyComponent::Update(float deltaTime)
{
	m_pCurrentAnimation->Update(deltaTime);

	if (m_CurrentState == EnemyState::Respawning)
	{
		m_RespawnTimer += deltaTime;
		if (m_RespawnTimer >= m_RespawnTime)
		{
			m_RespawnTimer = 0;
			Respawn();
		}
	}

	if (m_CurrentState == EnemyState::Dying)
	{
		m_PlayDeadTimer += deltaTime;
		if (m_PlayDeadTimer >= m_PlayDeadTime)
		{
			m_CurrentState = EnemyState::Respawning;
			m_PlayDeadTimer = 0.0f;
			m_pGameObject->SetPosition(-100, 0);
		}
	}
}

void dae::EnemyComponent::FixedUpdate(float)
{
}

void dae::EnemyComponent::OnCollision(GameObject*)
{
}

void dae::EnemyComponent::OnEndCollision(GameObject*)
{
}

dae::EnemyState dae::EnemyComponent::GetState() const
{
	return m_CurrentState;
}

void dae::EnemyComponent::HitByBurger()
{
	SwitchAnimation(EnemyState::Dying);
}

void dae::EnemyComponent::Respawn()
{
	m_pGameObject->SetPosition(m_StartX, m_StartY);
	SwitchAnimation(EnemyState::WalkingLeft);
}

void dae::EnemyComponent::SwitchAnimation(EnemyState state)
{
	if (state != m_CurrentState)
	{
		m_CurrentState = state;

		m_pCurrentAnimation->Reset();
		m_pCurrentAnimation = m_Animations.find(m_CurrentState)->second;
		m_pCurrentAnimation->Activate();
		m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture(m_pCurrentAnimation->GetSpriteSheet()));

	}
}
