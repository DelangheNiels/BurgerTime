#include "BurgerTimePCH.h"
#include "PeperComponent.h"
#include "EnemyComponent.h"

#include "RenderComponent.h"
#include "AnimatedSpriteComponent.h"
#include "ResourceManager.h"

dae::PeperComponent::PeperComponent(GameObject* gameObject, RenderComponent* renderComp, std::map<PlayerStates, AnimatedSpriteComponent*> animations)
	:Component(gameObject), m_pRenderComponent{renderComp}, m_Animations{animations}
{
	m_pRenderComponent->SetInActive();
	m_pCurrentAnimation = m_Animations.find(PlayerStates::Idle)->second;

	m_AnitmationTime = (3.0f * 0.4f) / 2.0f;
}

void dae::PeperComponent::Update(float deltaTime)
{
	if (m_Spawned)
	{
		m_AnimationTimer += deltaTime;
		if (m_AnimationTimer >= m_AnitmationTime)
		{
			m_AnimationTimer = 0;
			m_Spawned = false;
			SetInActive();
		}
	}
}

void dae::PeperComponent::OnCollision(GameObject* pOther)
{
	if (pOther->GetTag() == "Enemy" && pOther->GetComponent<EnemyComponent>()->GetState() != EnemyState::Dying && m_IsActive)
	{
		pOther->GetComponent<EnemyComponent>()->Stun();
	}
}

void dae::PeperComponent::Spawn(PlayerStates playerState)
{
	m_pRenderComponent->SetActive();
	m_pCurrentAnimation = m_Animations.find(playerState)->second;
	m_pCurrentAnimation->Reset();
	m_pCurrentAnimation->Activate();
	m_pRenderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture(m_pCurrentAnimation->GetSpriteSheet()));
	m_Spawned = true;
}

