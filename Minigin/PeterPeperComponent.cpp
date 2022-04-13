#include "MiniginPCH.h"
#include "PeterPeperComponent.h"
#include "PlayerHealthDisplayComponent.h"

void dae::PeterPeperComponent::IsDamaged()
{
	if (m_Health != 0)
	{
		--m_Health;

		for (size_t i = 0; i < m_Observers.size(); i++)
		{
			m_Observers.at(i)->TookDamage();
			
		}

		if (m_Health == 0)
		{
			for (size_t i = 0; i < m_Observers.size(); i++)
			{
				m_Observers.at(i)->IsDead();
			}
		}
	}
	
}

void dae::PeterPeperComponent::Update(float deltaTime)
{
	UpdatePosition(deltaTime);
}

int dae::PeterPeperComponent::GetLives() const
{
	return m_Health;
}

void dae::PeterPeperComponent::MoveLeft()
{
	m_MoveLeft = true;
}

void dae::PeterPeperComponent::MoveRight()
{
	m_MoveRight = true;
}

void dae::PeterPeperComponent::AddPlayerObserver(PlayerHealthDisplayComponent* observer)
{
	if (std::find(m_Observers.begin(), m_Observers.end(), observer) == m_Observers.end())
	{
		m_Observers.push_back(observer);
	
	}
}

void dae::PeterPeperComponent::RemovePlayerObserver(PlayerHealthDisplayComponent* observer)
{
	auto it = std::find(m_Observers.begin(), m_Observers.end(), observer);
	if ( it != m_Observers.end())
	{
		m_Observers.erase(it);
	}
}

dae::PeterPeperComponent::PeterPeperComponent(GameObject* gameObject, int health)
	:Component(gameObject), m_Health(health)
{
	if (m_Health <= 0)
	{
		m_Health = 1;
	}
}

void dae::PeterPeperComponent::UpdatePosition(float deltaTime)
{
	auto pos = m_pGameObject->GetTransform().GetPosition();
	if (m_MoveLeft)
	{
		pos.x -= m_MovementSpeed * deltaTime;
		std::cout << pos.x << " " << pos.y << "\n";
		m_pGameObject->SetPosition(pos.x, pos.y);
		std::cout << m_pGameObject->GetTransform().GetPosition().x << " | " << m_pGameObject->GetTransform().GetPosition().y << "\n";
	}

	if (m_MoveRight)
	{
		pos.x += deltaTime * m_MovementSpeed;
		m_pGameObject->SetPosition(pos.x, pos.y);
	}

	

	m_MoveLeft = false;
	m_MoveRight = false;
}
