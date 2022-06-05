#pragma once

#include "Component.h"

namespace dae
{
	class EnemyComponent;
	class AIMovementComponent final : public Component
	{
	public:
		AIMovementComponent(GameObject* gameObject, EnemyComponent* enemy);
		virtual ~AIMovementComponent() = default;
		AIMovementComponent(const AIMovementComponent & other) = default;
		AIMovementComponent(AIMovementComponent && other) = default;
		AIMovementComponent& operator=(const AIMovementComponent & other) = default;
		AIMovementComponent& operator=(AIMovementComponent && other) = default;

		void Update(float) override;
		void FixedUpdate(float) override;
		void OnCollision(GameObject*) override;

	private:
		float m_MovementSpeed = 120.0f;
		EnemyComponent* m_pEnemy{};
	};
}



