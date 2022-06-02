#include "BurgerTimePCH.h"
#include "PeterPeperComponent.h"
#include "PlayerHealthDisplayComponent.h"
#include "CollisionComponent.h"

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

void dae::PeterPeperComponent::Update(float)
{
	std::cout << m_pGameObject->GetTransform().GetPosition().x << " " << m_pGameObject->GetTransform().GetPosition().y << "\n";
}

void dae::PeterPeperComponent::FixedUpdate(float fixedTime)
{
	UpdatePosition(fixedTime);
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

void dae::PeterPeperComponent::MoveUp()
{
	if(m_CanMoveUp)
		m_MoveUp = true;
}

void dae::PeterPeperComponent::MoveDown()
{
	if(m_CanMoveDown)
		m_MoveDown = true;
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

void dae::PeterPeperComponent::SetOnGround(bool onGround)
{
	m_OnGround = onGround;
}


dae::PeterPeperComponent::PeterPeperComponent(GameObject* gameObject, int health)
	:Component(gameObject), m_Health(health)
{
	if (m_Health <= 0)
	{
		m_Health = 1;
	}
}

void dae::PeterPeperComponent::OnCollision(GameObject* object)
{
	const std::string tag = object->GetTag();

	if (tag == "Platform")
	{
		m_OnGround = true;
	}

	if (tag.find("Ladder") != std::string ::npos )
	{
		m_CanMoveDown = true;
		m_OnLadder = true;
		m_CanMoveUp = true;
	}

	if (tag == "TopBorder")
	{
		m_CanMoveUp = false;
		m_OnGround = true;
		if(!m_OnLadder)
			m_pGameObject->SetPosition(m_pGameObject->GetTransform().GetPosition().x, object->GetTransform().GetPosition().y + 1.1f);
	}

	if (tag == "BottomBorder")
	{
		m_CanMoveDown = false;
		m_OnGround = true;
		m_pGameObject->SetPosition(m_pGameObject->GetTransform().GetPosition().x, object->GetTransform().GetPosition().y - (m_pGameObject->GetComponent<CollisionComponent>()->GetBoundingBox().height + 1.1f));
	}
}

void dae::PeterPeperComponent::OnEndCollision(GameObject* object)
{
	const std::string tag = object->GetTag();

	if (tag == "Platform")
	{
		
		m_OnGround = false;
	}

	if (tag == "LadderUp")
	{
		m_CanMoveUp = false;
	}
}

void dae::PeterPeperComponent::UpdatePosition(float deltaTime)
{
	auto pos = m_pGameObject->GetTransform().GetPosition();
	if (m_OnGround)
	{
		
		if (m_MoveLeft)
		{
			pos.x -= m_MovementSpeed * deltaTime;
			m_pGameObject->SetPosition(pos.x, pos.y);
		}

		if (m_MoveRight)
		{
			pos.x += deltaTime * m_MovementSpeed;
			m_pGameObject->SetPosition(pos.x, pos.y);
		}

		m_MoveLeft = false;
		m_MoveRight = false;
	}

	if (m_OnLadder)
	{
		if (m_MoveDown)
		{
			pos.y += m_MovementSpeed * deltaTime;
			m_pGameObject->SetPosition(pos.x, pos.y);
		}

		if (m_MoveUp)
		{
			pos.y -= m_MovementSpeed * deltaTime;
			m_pGameObject->SetPosition(pos.x, pos.y);
		}

		m_MoveDown = false;
		m_MoveUp = false;
	}

	/*if(!m_OnGround && !m_OnLadder)
	{
		pos.y += deltaTime * 98.1f;
		m_pGameObject->SetPosition(pos.x, pos.y);
	}*/

	//m_OnGround = false;
	//m_OnLadder = false;
	
}
