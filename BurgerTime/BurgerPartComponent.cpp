#include "BurgerTimePCH.h"
#include "BurgerPartComponent.h"

#include "BurgerComponent.h"
#include "EnemyComponent.h"

dae::BurgerPartComponent::BurgerPartComponent(GameObject* gameObject)
	:Component(gameObject), m_State{BurgerState::OnGround}
{
}

void dae::BurgerPartComponent::Update(float)
{
}

void dae::BurgerPartComponent::FixedUpdate(float fixedTime)
{
	if (m_State == BurgerState::Falling)
	{
		m_pGameObject->SetPosition(m_pGameObject->GetTransform().GetPosition().x, m_pGameObject->GetTransform().GetPosition().y + (m_FallingSpeed * fixedTime));
	}
}

void dae::BurgerPartComponent::OnCollision(GameObject* other)
{
	const std::string tag = other->GetTag();

	switch (m_State)
	{
	case dae::BurgerState::Hit:
		break;
	case dae::BurgerState::OnGround:
	{
		if (other->GetTag() == "Player")
		{
			m_State = BurgerState::Hit;
			m_pGameObject->SetPosition(m_pGameObject->GetTransform().GetPosition().x, m_pGameObject->GetTransform().GetPosition().y + m_DropAmount);

			if (m_pBurger)
			{
				m_pBurger->NotifyHit();
			}

			std::cout << "hit" << "\n";
		}

		if (other->GetTag() == "BurgerPart" && other->GetComponent<BurgerPartComponent>()->GetState() != BurgerState::OnCatcher)
		{
			m_State = BurgerState::Hit;
			m_pGameObject->SetPosition(m_pGameObject->GetTransform().GetPosition().x, m_pGameObject->GetTransform().GetPosition().y + m_DropAmount);
			if (m_pBurger)
			{
				m_pBurger->NotifyHit();
			}
		}
		break;
	}
	case dae::BurgerState::Falling:
	{
		if ((tag == "MrHotdog" || tag == "MrEgg" || tag == "MrPickle") && other->GetComponent<EnemyComponent>()->GetState() != EnemyState::Dying)
		{
			other->GetComponent<EnemyComponent>()->HitByBurger();
			m_pBurger->NotifyHitEnemy(other);
		}

		if (other->GetTag() == "BottomBorder")
		{
			m_State = BurgerState::OnGround;
			if (m_pBurger)
			{
				m_pBurger->NotifyOnGround();
			}
		}

		if (other->GetTag() == "Catcher")
		{
			m_State = BurgerState::OnCatcher;
			if (m_pBurger)
			{
				m_pBurger->NotifyOnCatcher();
			}
		}

		if (other->GetTag() == "BurgerPart" && other->GetComponent<BurgerPartComponent>() && other->GetComponent<BurgerPartComponent>()->GetState() == BurgerState::OnCatcher)
		{
			m_pBurger->NotifyOnCatcher();	
		}
		break;
	}
	case dae::BurgerState::OnCatcher:
		break;
	default:
		break;
	}
}

void dae::BurgerPartComponent::SetBurger(BurgerComponent* burger)
{
	m_pBurger =  burger;
}

void dae::BurgerPartComponent::Drop()
{
	m_State = BurgerState::Falling;
}

void dae::BurgerPartComponent::StopDropping()
{
	if (m_State == BurgerState::Falling)
	{
		m_State = BurgerState::OnGround;
	}
}

void dae::BurgerPartComponent::OnCatcher()
{
	m_State = BurgerState::OnCatcher;
}

dae::BurgerState dae::BurgerPartComponent::GetState() const
{
	return m_State;
}

