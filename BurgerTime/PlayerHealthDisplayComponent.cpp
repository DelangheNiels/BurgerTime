#include "BurgerTimePCH.h"
#include "PlayerHealthDisplayComponent.h"

#include "GameManager.h"

dae::PlayerHealthDisplayComponent::PlayerHealthDisplayComponent(GameObject* gameObject,PeterPeperComponent* player,const std::shared_ptr<TextComponent>& textComponent)
	:Component(gameObject),m_pObservedPlayer(player), m_pTextComponent(textComponent)
{
	m_pTextComponent.get()->SetText("Lives: " + std::to_string(m_pObservedPlayer->GetLives()));

	//observer adds itself to the player
	if (m_pObservedPlayer != nullptr)
	{
		m_pObservedPlayer->AddPlayerObserver(this);
	}
	

}

void dae::PlayerHealthDisplayComponent::IsDead()
{
		std::cout << "Player is dead" << "\n";
		GameManager::GetInstance().NotifyPlayerDied(m_pObservedPlayer);
}

void dae::PlayerHealthDisplayComponent::TookDamage()
{
	if (m_pObservedPlayer != nullptr)
	{
		std::string lives = std::to_string(m_pObservedPlayer->GetLives());
		m_pTextComponent.get()->SetText("Lives: " + lives);
	}
}

void dae::PlayerHealthDisplayComponent::Update(float)
{
}

void dae::PlayerHealthDisplayComponent::SetObservedPlayer(PeterPeperComponent* player)
{
	m_pObservedPlayer = player;
}

void dae::PlayerHealthDisplayComponent::printPlayer()
{
	std::cout << m_pObservedPlayer << "\n";
}

//void dae::PlayerHealthDisplayComponent::AddObservedPlayer(std::shared_ptr<PeterPeperComponent> player)
//{
//	if (m_pObservedPlayer == nullptr)
//	{
//		m_pObservedPlayer = std::make_shared<PeterPeperComponent>(player);
//	}
//
//	else
//	{
//		if (m_pObservedPlayer != player)
//		{
//			m_pObservedPlayer = nullptr;
//			m_pObservedPlayer = std::make_shared<PeterPeperComponent>(player);
//		}
//	}
//}
//
//void dae::PlayerHealthDisplayComponent::RemoveObservedPlayer(std::shared_ptr<PeterPeperComponent> player)
//{
//	if (m_pObservedPlayer != nullptr)
//	{
//		if (m_pObservedPlayer == player)
//		{
//			m_pObservedPlayer = nullptr;
//		}
//	}
//}
