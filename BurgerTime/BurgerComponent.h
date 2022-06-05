#pragma once

#include "Component.h"

namespace dae
{
	class BurgerPartComponent;
	class PointsComponent;

	class BurgerComponent : public Component
	{
	public:
		BurgerComponent(GameObject* gameObject, PointsComponent* pointsComp);
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
		void NotifyHitEnemy(GameObject* enemy);

		std::vector<BurgerPartComponent*> Getparts() const;

	private:
		std::vector<BurgerPartComponent*> m_Parts{};
		std::vector<GameObject*> m_EnemiesHit{};
		PointsComponent* m_pPointsComponent{};

		int m_AmountOfHitparts{};
	};
}


