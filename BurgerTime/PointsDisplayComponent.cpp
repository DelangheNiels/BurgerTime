#include "BurgerTimePCH.h"
#include "PointsDisplayComponent.h"

dae::PointsDisplayComponent::PointsDisplayComponent(GameObject* gameObject, std::shared_ptr<TextComponent> textComponent)
	:Component(gameObject), m_pTextComponent(textComponent), m_TotalPoints(0)
{
	m_pTextComponent.get()->SetText("Points: " + std::to_string(m_TotalPoints));
}

void dae::PointsDisplayComponent::Update(float)
{
}

void dae::PointsDisplayComponent::AddPoints(int points)
{
	m_TotalPoints += points;
	m_pTextComponent.get()->SetText("Points: " + std::to_string(m_TotalPoints));
}
