#include "BurgerTimePCH.h"
#include "PointsComponent.h"

dae::PointsComponent::PointsComponent(GameObject* gameObject)
    :Component(gameObject)
{
}

void dae::PointsComponent::Update(float )
{
}

int dae::PointsComponent::GetPoints() const
{
    return m_Points;
}

void dae::PointsComponent::PartDropped()
{
    for (size_t i = 0; i < m_PointsObservers.size(); i++)
    {
        m_PointsObservers.at(i)->BurgerPartDropped();
    }
}

void dae::PointsComponent::AddPointsObserver(PointsObserver* pointsObserver)
{
    if (std::find(m_PointsObservers.begin(), m_PointsObservers.end(), pointsObserver) == m_PointsObservers.end())
    {
        m_PointsObservers.push_back(pointsObserver);
    }
}

void dae::PointsComponent::RemovePointsObserver(PointsObserver* pointsObserver)
{
    auto it = std::find(m_PointsObservers.begin(), m_PointsObservers.end(), pointsObserver);

    if (it != m_PointsObservers.end())
    {
        m_PointsObservers.erase(it);
    }
}

