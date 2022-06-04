#pragma once

#include "Component.h"
#include <map>

namespace dae
{
	class AnimatedSpriteComponent;
	class RenderComponent;

	enum class EnemyState
	{
		WalkingLeft, WalkingRight, WalkingUp, WalkingDown, Dying
	};

	class MrHotdogComponent final : public Component
	{
	public:
		explicit MrHotdogComponent(GameObject* gameObject, RenderComponent* renderComp, std::map<EnemyState, AnimatedSpriteComponent*> animations);
		virtual ~MrHotdogComponent() = default;
		MrHotdogComponent(const MrHotdogComponent & other) = default;
		MrHotdogComponent(MrHotdogComponent && other) = default;
		MrHotdogComponent& operator=(const MrHotdogComponent & other) = default;
		MrHotdogComponent& operator=(MrHotdogComponent && other) = default;

		void Update(float) override;
		void FixedUpdate(float) override;

		void OnCollision(GameObject*) override;
		void OnEndCollision(GameObject*) override;

		float GetPoints() const;
		EnemyState GetState() const;

	private:
		std::map<EnemyState, AnimatedSpriteComponent*> m_Animations;

		EnemyState m_CurrentState;
		AnimatedSpriteComponent* m_pCurrentAnimation;
		RenderComponent* m_pRenderComponent;

		float m_Points = 100;

		float m_MovementSpeed = { 90.0f };


	};
}


