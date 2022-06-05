#pragma once
#include "Component.h"
#include "PlayerHealthDisplayComponent.h"

#include <vector>
#include <map>

namespace dae
{
	class PlayerHealthDisplayComponent;
	class AnimatedSpriteComponent;
	class RenderComponent;

	enum class PlayerStates
	{
		Idle, WalkingLeft, WalkingRight, ClimbingUp, ClimbingDown, Dying
	};

	class PeterPeperComponent final : public Component
	{
	public:

		void IsDamaged();

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedTime) override;
		int GetLives() const;

		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();

		void StopMoveLeft();
		void StopMoveRight();
		void StopMoveUp();
		void StopMoveDown();

		void AddPlayerObserver(PlayerHealthDisplayComponent* observer);
		void RemovePlayerObserver(PlayerHealthDisplayComponent* observer);

		void SetOnGround(bool onGround);

		PeterPeperComponent(GameObject* gameObject, int health,RenderComponent* renderComp ,std::map<PlayerStates, AnimatedSpriteComponent*> animations, float startX, float startY);
		virtual ~PeterPeperComponent() = default;
		PeterPeperComponent(const PeterPeperComponent& other) = default;
		PeterPeperComponent(PeterPeperComponent&& other) = default;
		PeterPeperComponent& operator=(const PeterPeperComponent& other) = default;
		PeterPeperComponent& operator=(PeterPeperComponent&& other) = default;

		void OnCollision(GameObject*) override;
		void OnEndCollision(GameObject*)override;

	private:
		int m_Health;
		std::vector<PlayerHealthDisplayComponent*> m_Observers{};

		bool m_MoveLeft{ false };
		bool m_MoveRight{ false };
		bool m_MoveUp{ false };
		bool m_MoveDown{ false };

		bool m_OnGround{ false };
		bool m_CanMoveUp{ false };
		bool m_CanMoveDown{ false };
		bool m_OnLadder{ false };

		float m_MovementSpeed{ 80.0f };

		float m_RespawnTimer = 0.0f;
		float m_RespawnTime = 0.0f;

		float m_Startx, m_StartY;

		bool m_FirsFrame{ true };

		std::map<PlayerStates, AnimatedSpriteComponent*> m_Animations;
		
		PlayerStates m_CurrentState;
		AnimatedSpriteComponent* m_pCurrentAnimation;
		RenderComponent* m_pRenderComponent;

		int m_AmountOfPepers{};


		void UpdatePosition(float deltaTime);
		void UpdateAnimation(float deltaTime);

		void SetIdle();

		void SwitchAnimation(PlayerStates state);

		void Respawn();
	};

}


