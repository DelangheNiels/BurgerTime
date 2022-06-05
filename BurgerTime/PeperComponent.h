#pragma once

#include "Component.h"
#include <map>
#include "PeterPeperComponent.h"

namespace dae
{
	class PeperComponent final : public Component
	{
	public: 
		PeperComponent(GameObject* gameObject, RenderComponent* renderComp, std::map<PlayerStates, AnimatedSpriteComponent*> animations);
		virtual ~PeperComponent() = default;
		PeperComponent(const PeperComponent & other) = default;
		PeperComponent(PeperComponent && other) = default;
		PeperComponent& operator=(const PeperComponent & other) = default;
		PeperComponent& operator=(PeperComponent && other) = default;

	private:
		float m_StartX{}, m_StartY{};
	};
}


