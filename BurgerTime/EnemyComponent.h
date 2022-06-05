#pragma once

#include "Component.h"
#include <map>

namespace dae
{
	class AnimatedSpriteComponent;
	class RenderComponent;

	enum class EnemyState
	{
		WalkingLeft, WalkingRight, WalkingUp, WalkingDown, Dying, Respawning
	};

	class EnemyComponent final : public Component
	{
	public:
		EnemyComponent(GameObject* gameObject, RenderComponent* renderComp, std::map<EnemyState, AnimatedSpriteComponent*> animations, float startPosX, float startPosY);
		virtual ~EnemyComponent() = default;
		EnemyComponent(const EnemyComponent& other) = default;
		EnemyComponent(EnemyComponent&& other) = default;
		EnemyComponent& operator=(const EnemyComponent& other) = default;
		EnemyComponent& operator=(EnemyComponent&& other) = default;

		void Update(float) override;

		EnemyState GetState() const;

		void HitByBurger();
		void Stun();

		void Respawn();

		float m_PlayDeadTimer = 0.0f;
		float m_PlayDeadTime = 0;
		float m_RespawnTimer = 0.0f;
		float m_RespawnTime = 5.0f;

		float m_StartX{}, m_StartY{};

	private:
		std::map<EnemyState, AnimatedSpriteComponent*> m_Animations;

		EnemyState m_CurrentState;
		AnimatedSpriteComponent* m_pCurrentAnimation;
		RenderComponent* m_pRenderComponent;

		void SwitchAnimation(EnemyState state);


	};
}


