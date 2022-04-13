#pragma once
#include "Component.h"

namespace dae
{
	class PlatformComponent final : public Component
	{
	public:
		explicit PlatformComponent(GameObject* gameObject);
		virtual ~PlatformComponent() = default;
		PlatformComponent(const PlatformComponent & other) = delete;
		PlatformComponent(PlatformComponent && other) = delete;
		PlatformComponent& operator=(const PlatformComponent & other) = delete;
		PlatformComponent& operator=(PlatformComponent && other) = delete;

		void Update(float deltaTime) override;
	};
}


