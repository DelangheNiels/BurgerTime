#include "MiniginPCH.h"
#include "CollisionComponent.h"

dae::CollisionComponent::CollisionComponent(GameObject* gameObject, BoundingBox boundingBox)
	:Component(gameObject), m_BoundingBox(boundingBox)
{
}

void dae::CollisionComponent::Update(float)
{
}

void dae::CollisionComponent::CheckCollision(const BoundingBox& boundingBox, GameObject* pOther)
{
	float myXmin = GetGameObject()->GetTransform().GetPosition().x;
	float myXmax = myXmin + m_BoundingBox.width;
	float myYmin = GetGameObject()->GetTransform().GetPosition().y;
	float myYmax = myYmin + m_BoundingBox.height;

	float otherXmin = pOther->GetTransform().GetPosition().x;
	float otherXmax = otherXmin + boundingBox.width;
	float otherYmin = pOther->GetTransform().GetPosition().y;
	float otherYmax = otherYmin + boundingBox.height;

	bool isColliding = (myXmin < otherXmax&& otherXmin < myXmax&& myYmin < otherYmax&& otherYmin < myYmax);
	bool alreadyColliding = std::find(m_CollidingObjects.begin(), m_CollidingObjects.end(), pOther) != m_CollidingObjects.end();

	if (isColliding)
	{
		m_pGameObject->OnCollision(pOther);
		if(!alreadyColliding)
			m_CollidingObjects.push_back(pOther);
	}

	if (!isColliding && alreadyColliding && m_CollidingObjects.size() > 0)
	{
		m_pGameObject->OnEndCollision(pOther);
		m_CollidingObjects.erase(std::find(m_CollidingObjects.begin(), m_CollidingObjects.end(), pOther));
	}
}

dae::BoundingBox dae::CollisionComponent::GetBoundingBox() const
{
	return m_BoundingBox;
}


