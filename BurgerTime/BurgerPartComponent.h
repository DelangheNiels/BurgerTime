#pragma once

#include "Component.h"

namespace dae
{
	class BurgerComponent;

	enum class BurgerState
	{
		Hit, Falling, OnGround, OnCatcher
	};

	class BurgerPartComponent final : public Component
	{
	public:
		explicit BurgerPartComponent(GameObject* gameObject);
		virtual ~BurgerPartComponent() = default;
		BurgerPartComponent(const BurgerPartComponent & other) = default;
		BurgerPartComponent(BurgerPartComponent && other) = default;
		BurgerPartComponent& operator=(const BurgerPartComponent & other) = default;
		BurgerPartComponent& operator=(BurgerPartComponent && other) = default;

		void Update(float) override;
		void FixedUpdate(float fixedTime) override;
		void OnCollision(GameObject*) override;

		void SetBurger(BurgerComponent* burger);

		void Drop();
		void StopDropping();
		void OnCatcher();

		BurgerState GetState() const;

	private:

		BurgerState m_State;

		float m_FallingSpeed = 110.0f;
		float m_DropAmount = 28.0f;

		BurgerComponent* m_pBurger{};


	};
}


