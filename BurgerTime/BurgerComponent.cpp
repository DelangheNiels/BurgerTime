#include "BurgerTimePCH.h"
#include "BurgerComponent.h"

#include "BurgerPartComponent.h"

dae::BurgerComponent::BurgerComponent(GameObject* gameObject)
	:Component(gameObject), m_AmountOfHitparts{0}
{
}

void dae::BurgerComponent::Update(float)
{
}

void dae::BurgerComponent::AddPart(BurgerPartComponent* part)
{
	m_Parts.emplace_back(part);
	part->SetBurger(this);
}

void dae::BurgerComponent::NotifyHit()
{
	++m_AmountOfHitparts;
	if (m_AmountOfHitparts >= int(m_Parts.size()))
	{
		m_AmountOfHitparts = 0;

		std::for_each(m_Parts.begin(), m_Parts.end(), [](BurgerPartComponent* part) {part->Drop(); });
	}
}

void dae::BurgerComponent::NotifyOnGround()
{
	std::for_each(m_Parts.begin(), m_Parts.end(), [](BurgerPartComponent* part) {part->StopDropping(); });
}

void dae::BurgerComponent::NotifyOnCatcher()
{
	std::for_each(m_Parts.begin(), m_Parts.end(), [](BurgerPartComponent* part) {part->OnCatcher(); });
}

std::vector<dae::BurgerPartComponent*> dae::BurgerComponent::Getparts() const
{
	return m_Parts;
}
