#pragma once
#include "PointsObserver.h"
#include "TextComponent.h"
namespace dae
{
	class PointsDisplayComponent final : public PointsObserver, public Component
	{
	public:
		explicit PointsDisplayComponent(GameObject* gameObject, std::shared_ptr<TextComponent> textComponent);
		~PointsDisplayComponent() = default;

		void Update(float deltaTime) override;
		void BurgerPartDropped() override;
		void MrHotdogHit() override;

		PointsDisplayComponent(const PointsDisplayComponent& other) = delete;
		PointsDisplayComponent(PointsDisplayComponent&& other) = delete;
		PointsDisplayComponent& operator=(const PointsDisplayComponent& other) = delete;
		PointsDisplayComponent& operator=(PointsDisplayComponent&& other) = delete;

	private:
		int m_TotalPoints;
		std::shared_ptr<TextComponent> m_pTextComponent{};

		int m_PointsDropPart = 50;
		int m_PointsMrHotdog = 100;
	};
}


