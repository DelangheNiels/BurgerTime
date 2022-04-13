#pragma once
#include "Component.h"
#include "PlayerHealthDisplayComponent.h"

namespace dae
{
	class PlayerHealthDisplayComponent;
	class PeterPeperComponent : public Component
	{
	public:

		void IsDamaged();

		void Update(float deltaTime) override;
		int GetLives() const;

		void MoveLeft();
		void MoveRight();

		void AddPlayerObserver(PlayerHealthDisplayComponent* observer);
		void RemovePlayerObserver(PlayerHealthDisplayComponent* observer);

		explicit PeterPeperComponent(GameObject* gameObject, int health);
		virtual ~PeterPeperComponent() = default;
		PeterPeperComponent(const PeterPeperComponent& other) = default;
		PeterPeperComponent(PeterPeperComponent&& other) = default;
		PeterPeperComponent& operator=(const PeterPeperComponent& other) = default;
		PeterPeperComponent& operator=(PeterPeperComponent&& other) = default;

	private:
		int m_Health;
		std::vector<PlayerHealthDisplayComponent*> m_Observers{};

		bool m_MoveLeft{ false };
		bool m_MoveRight{ false };

		float m_MovementSpeed{ 50.0f };

		void UpdatePosition(float deltaTime);
	};

}


