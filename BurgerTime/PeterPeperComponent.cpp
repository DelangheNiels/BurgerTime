#include "BurgerTimePCH.h"

#include "PeterPeperComponent.h"
#include "PlayerHealthDisplayComponent.h"
#include "CollisionComponent.h"
#include "AnimatedSpriteComponent.h"
#include "RenderComponent.h"

#include "ResourceManager.h"
#include "EnemyComponent.h"

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
	//std::cout << m_pGameObject->GetTransform().GetPosition().x << " " << m_pGameObject->GetTransform().GetPosition().y << "\n";
	SetIdle();
	UpdateAnimation(deltaTime);

	if (m_CurrentState == PlayerStates::Dying)
	{
		m_RespawnTimer += deltaTime;
		if (m_RespawnTimer >= m_RespawnTime)
		{
			Respawn();
		}
	}
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
	if (m_OnGround && m_CurrentState != PlayerStates::Dying)
	{
		m_MoveLeft = true;
		SwitchAnimation(PlayerStates::WalkingLeft);
	}

}

void dae::PeterPeperComponent::MoveRight()
{
	if (m_OnGround && m_CurrentState != PlayerStates::Dying)
	{
		m_MoveRight = true;
		SwitchAnimation(PlayerStates::WalkingRight);
	}
}

void dae::PeterPeperComponent::MoveUp()
{
	if (m_CanMoveUp && m_CurrentState != PlayerStates::Dying)
	{
		m_MoveUp = true;
		SwitchAnimation(PlayerStates::ClimbingUp);
	}
		
}

void dae::PeterPeperComponent::MoveDown()
{
	if (m_CanMoveDown && m_CurrentState != PlayerStates::Dying)
	{
		m_MoveDown = true;
		SwitchAnimation(PlayerStates::ClimbingDown);
	}
}

void dae::PeterPeperComponent::StopMoveLeft()
{
	m_MoveLeft = false;
}

void dae::PeterPeperComponent::StopMoveRight()
{
	m_MoveRight = false;
}

void dae::PeterPeperComponent::StopMoveUp()
{
	m_MoveUp = false;
}

void dae::PeterPeperComponent::StopMoveDown()
{
	m_MoveDown = false;
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


dae::PeterPeperComponent::PeterPeperComponent(GameObject* gameObject, int health, RenderComponent* renderComp, std::map<PlayerStates, AnimatedSpriteComponent*> animations, float startX, float startY)
	:Component(gameObject), m_Health(health), m_Animations(animations), m_pRenderComponent(renderComp), m_Startx{ startX }, m_StartY{ startY }
{
	m_pGameObject->SetPosition(startX, startY);
	if (m_Health <= 0)
	{
		m_Health = 1;
	}

	m_RespawnTime = ((animations.find(PlayerStates::Dying)->second->GetAmountOfAnimations()-1) * (animations.find(PlayerStates::Dying)->second->GetChangeImageTime()))/2;

	m_CurrentState = PlayerStates::Idle;
	m_pCurrentAnimation = m_Animations.find(m_CurrentState)->second;
	
}

void dae::PeterPeperComponent::OnCollision(GameObject* object)
{
	const std::string tag = object->GetTag();

	if ( (tag == "MrHotdog" || tag == "MrEgg" || tag =="MrPickle") && m_CurrentState != PlayerStates::Dying && object->GetComponent<EnemyComponent>()->GetState() != EnemyState::Dying)
	{
		SwitchAnimation(PlayerStates::Dying);
		IsDamaged();
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
		m_pGameObject->SetPosition(m_pGameObject->GetTransform().GetPosition().x, object->GetTransform().GetPosition().y - (m_pGameObject->GetComponent<CollisionComponent>()->GetBoundingBox().height)-1.5f);
	}
}

void dae::PeterPeperComponent::OnEndCollision(GameObject* object)
{
	const std::string tag = object->GetTag();

	if (tag == "LadderUp")
	{
		m_CanMoveUp = false;
		m_OnGround = true;
	}

	if (tag == "LadderDown")
	{
		m_CanMoveDown = false;
		m_OnGround = true;
	}
}

void dae::PeterPeperComponent::UpdatePosition(float deltaTime)
{
	if (m_CurrentState != PlayerStates::Dying)
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
		}

		m_OnLadder = false;
	}
	
}

void dae::PeterPeperComponent::UpdateAnimation(float deltaTime)
{
	m_pCurrentAnimation->Update(deltaTime);
}

void dae::PeterPeperComponent::SetIdle()
{
	if (!m_MoveDown && !m_MoveLeft && !m_MoveUp && !m_MoveRight && m_CurrentState != PlayerStates::Dying)
	{
		SwitchAnimation(PlayerStates::Idle);
	}
}

void dae::PeterPeperComponent::SwitchAnimation(PlayerStates state)
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

void dae::PeterPeperComponent::Respawn()
{
	m_pGameObject->SetPosition(m_Startx, m_StartY);
	SwitchAnimation(PlayerStates::Idle);
	m_RespawnTimer = 0.0f;
}
