#include "MiniginPCH.h"
#include "PointsComponent.h"

dae::PointsComponent::PointsComponent(GameObject* gameObject, int points /*PointsAchievementObserver* pPointsAchievementObserver*/)
    :Component(gameObject), m_Points{points} //m_pPointsAchievementObserver{pPointsAchievementObserver}
{
}

void dae::PointsComponent::Update(float )
{
}

int dae::PointsComponent::GetPoints() const
{
    return m_Points;
}

void dae::PointsComponent::IncreasePoints()
{
    for (size_t i = 0; i < m_PointsObservers.size(); i++)
    {
        m_PointsObservers.at(i)->AddPoints(m_Points);
    }

    //m_pPointsAchievementObserver->AddScore(m_Points);
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
