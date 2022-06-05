#include "BurgerTimePCH.h"
#include "AIMovementComponent.h"
#include <string>

#include "EnemyComponent.h"

dae::AIMovementComponent::AIMovementComponent(GameObject* gameObject, EnemyComponent* enemy)
	:Component(gameObject), m_pEnemy{enemy}
{
}

void dae::AIMovementComponent::Update(float)
{
}

void dae::AIMovementComponent::FixedUpdate(float fixedTime)
{
	if(m_pEnemy->GetState() != EnemyState::Dying)
		m_pGameObject->SetPosition(m_pGameObject->GetTransform().GetPosition().x + (m_MovementSpeed * fixedTime), m_pGameObject->GetTransform().GetPosition().y);

}

void dae::AIMovementComponent::OnCollision(GameObject* pOther)
{
	std::string tag = pOther->GetTag();

	if (tag == "LeftBorder" && m_MovementSpeed < 0)
	{
		m_MovementSpeed *= -1;
	}

	if (tag == "RightBorder" && m_MovementSpeed > 0)
	{
		m_MovementSpeed *= -1;
	}
}
