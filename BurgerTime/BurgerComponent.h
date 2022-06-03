#pragma once

#include "Component.h"

namespace dae
{
	class BurgerPartComponent;

	class BurgerComponent : public Component
	{
	public:
		explicit BurgerComponent(GameObject* gameObject);
		virtual ~BurgerComponent() = default;
		BurgerComponent(const BurgerComponent & other) = default;
		BurgerComponent(BurgerComponent && other) = default;
		BurgerComponent& operator=(const BurgerComponent & other) = default;
		BurgerComponent& operator=(BurgerComponent && other) = default;

		void Update(float) override;

		void AddPart(BurgerPartComponent* part);
		void NotifyHit();
		void NotifyOnGround();
		void NotifyOnCatcher();

		std::vector<BurgerPartComponent*> Getparts() const;

	private:
		std::vector<BurgerPartComponent*> m_Parts;

		int m_AmountOfHitparts{};
	};
}


