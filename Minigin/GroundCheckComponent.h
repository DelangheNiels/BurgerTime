#pragma once

#include "Component.h"

namespace dae
{
	class GroundCheckComponent final : public Component
	{
	public:
		explicit GroundCheckComponent(GameObject* gameObject);
		virtual ~GroundCheckComponent() = default;
		GroundCheckComponent(const GroundCheckComponent & other) = delete;
		GroundCheckComponent(GroundCheckComponent && other) = delete;
		GroundCheckComponent& operator=(const GroundCheckComponent & other) = delete;
		GroundCheckComponent& operator=(GroundCheckComponent && other) = delete;

		bool CheckOnGround(GameObject *otherObject);
		void Update(float deltaTime) override;
	};
}


