#pragma once
#include "Component.h"
#include "PointsObserver.h"

namespace dae
{
	class PointsComponent final : public Component
	{
	public:
		explicit PointsComponent(GameObject* gameObject);
		~PointsComponent() = default;

		void Update(float deltaTime) override;

		int GetPoints() const;
		void PartDropped();
		void MrHotdogHit();

		void AddPointsObserver(PointsObserver* pointsObserver);
		void RemovePointsObserver(PointsObserver* pointsObserver);

		PointsComponent(const PointsComponent & other) = delete;
		PointsComponent(PointsComponent && other) = delete;
		PointsComponent& operator=(const PointsComponent & other) = delete;
		PointsComponent& operator=(PointsComponent && other) = delete;

	private:

		int m_Points;
		std::vector<PointsObserver*> m_PointsObservers{};
	};
}


