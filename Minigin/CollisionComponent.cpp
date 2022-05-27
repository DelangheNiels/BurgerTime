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

	if (myXmin < otherXmax && otherXmin < myXmax
		&& myYmin < otherYmax && otherYmin < myYmax)
	{
		m_pGameObject->OnCollision(pOther);
	}

}

dae::BoundingBox dae::CollisionComponent::GetBoundingBox() const
{
	return m_BoundingBox;
}


