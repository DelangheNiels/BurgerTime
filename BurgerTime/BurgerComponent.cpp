#include "BurgerTimePCH.h"
#include "BurgerComponent.h"

#include "BurgerPartComponent.h"
#include "PointsComponent.h"

dae::BurgerComponent::BurgerComponent(GameObject* gameObject, PointsComponent* pointsComp)
	:Component(gameObject), m_AmountOfHitparts{0}, m_pPointsComponent{pointsComp}
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
		m_pPointsComponent->PartDropped();
	}
}

void dae::BurgerComponent::NotifyOnGround()
{
	std::for_each(m_Parts.begin(), m_Parts.end(), [](BurgerPartComponent* part) {part->StopDropping(); });
	m_EnemiesHit.clear();
}

void dae::BurgerComponent::NotifyOnCatcher()
{
	std::for_each(m_Parts.begin(), m_Parts.end(), [](BurgerPartComponent* part) {part->OnCatcher(); });
	m_EnemiesHit.clear();
}

void dae::BurgerComponent::NotifyHitEnemy(GameObject* enemy)
{
	if (std::find(m_EnemiesHit.begin(), m_EnemiesHit.end(), enemy) == m_EnemiesHit.end())
	{
		m_EnemiesHit.emplace_back(enemy);
		m_pPointsComponent->MrHotdogHit();
	}
}

std::vector<dae::BurgerPartComponent*> dae::BurgerComponent::Getparts() const
{
	return m_Parts;
}
