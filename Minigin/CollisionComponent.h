#pragma once

#include "Component.h"

namespace dae
{
	struct BoundingBox
	{
		float width, height;
	};

	class CollisionComponent final : public Component
	{
	public:
		CollisionComponent(GameObject* gameObject, BoundingBox boundingBox);
		virtual ~CollisionComponent() = default;
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;

		void Update(float deltaTime) override;
		void CheckCollision(const BoundingBox& boundingBox, GameObject* pOther);

		BoundingBox GetBoundingBox() const;

	private:
		BoundingBox m_BoundingBox;
		std::vector<GameObject*> m_CollidingObjects{};

	};
}


