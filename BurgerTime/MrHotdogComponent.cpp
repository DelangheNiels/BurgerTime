#include "BurgerTimePCH.h"
#include "MrHotdogComponent.h"

#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "AnimatedSpriteComponent.h"
#include "PeterPeperComponent.h"
#include "ResourceManager.h"
#include "BurgerPartComponent.h"

dae::MrHotdogComponent::MrHotdogComponent(GameObject* gameObject,RenderComponent* renderComp, std::map<EnemyState, AnimatedSpriteComponent*> animations, float startPosX, float startPosY)
	:Component(gameObject), m_pRenderComponent{renderComp}, m_Animations{animations}, m_StartX{startPosX}, m_StartY{startPosY}
{
	m_pGameObject->SetPosition(m_StartX, m_StartY);
	m_CurrentState = EnemyState::WalkingLeft;
	m_pCurrentAnimation = m_Animations.find(m_CurrentState)->second;
	m_pCurrentAnimation->Activate();
	m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture(m_pCurrentAnimation->GetSpriteSheet()));
	m_PlayDeadTime = ((animations.find(EnemyState::Dying)->second->GetAmountOfAnimations() - 1) * (animations.find(EnemyState::Dying)->second->GetChangeImageTime())) / 2;
}

void dae::MrHotdogComponent::Update(float deltaTime)
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

void dae::MrHotdogComponent::FixedUpdate(float)
{
}

void dae::MrHotdogComponent::OnCollision(GameObject* pOther)
{
	std::string tag = pOther->GetTag();
	if (tag == "BurgerPart" && pOther->GetComponent<BurgerPartComponent>()->GetState() == BurgerState::Falling && m_CurrentState != EnemyState::Dying)
	{
		std::cout << "dead" << "\n";
		SwitchAnimation(EnemyState::Dying);
		
	}
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

void dae::MrHotdogComponent::Respawn()
{
	m_pGameObject->SetPosition(m_StartX, m_StartY);
	SwitchAnimation(EnemyState::WalkingLeft);
}

void dae::MrHotdogComponent::SwitchAnimation(EnemyState state)
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
