#include "BurgerTimePCH.h"
#include "PointsDisplayComponent.h"
#include "HighscoreManager.h"

dae::PointsDisplayComponent::PointsDisplayComponent(GameObject* gameObject, std::shared_ptr<TextComponent> textComponent)
	:Component(gameObject), m_pTextComponent(textComponent), m_TotalPoints(0)
{
	m_pTextComponent.get()->SetText("Points: " + std::to_string(m_TotalPoints));
}

void dae::PointsDisplayComponent::Update(float)
{
}

void dae::PointsDisplayComponent::BurgerPartDropped()
{
	m_TotalPoints += m_PointsDropPart;
	m_pTextComponent.get()->SetText("Points: " + std::to_string(m_TotalPoints));
	HighscoreManager::GetInstance().SetCurrentScore(m_TotalPoints);
}

void dae::PointsDisplayComponent::MrHotdogHit()
{
	m_TotalPoints += m_PointsMrHotdog;
	m_pTextComponent.get()->SetText("Points: " + std::to_string(m_TotalPoints));
	HighscoreManager::GetInstance().SetCurrentScore(m_TotalPoints);
}



