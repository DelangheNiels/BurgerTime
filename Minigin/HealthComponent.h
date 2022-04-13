#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace dae
{
	class HealthComponent final : public Component
	{
	public:
		void Update(float deltaTime) override;

		explicit HealthComponent(GameObject* gameObject, const std::shared_ptr<TextComponent>& textComponent);
		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent & other) = delete;
		HealthComponent(HealthComponent && other) = delete;
		HealthComponent& operator=(const HealthComponent & other) = delete;
		HealthComponent& operator=(HealthComponent && other) = delete;

	private:
		std::shared_ptr<TextComponent> m_TextComponent{nullptr};
		int m_Health;
	};
}


