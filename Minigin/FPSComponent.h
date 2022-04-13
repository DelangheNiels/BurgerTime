#pragma once
#include "Component.h"

namespace dae
{
	class Font;
	class TextComponent;
	class FPSComponent final : public Component
	{
	public:

		void Update(float deltaTime) override;

		explicit FPSComponent(GameObject* gameObject,const std::shared_ptr<TextComponent>& textComponent);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent & other) = delete;
		FPSComponent(FPSComponent && other) = delete;
		FPSComponent& operator=(const FPSComponent & other) = delete;
		FPSComponent& operator=(FPSComponent && other) = delete;

	private:
		float m_ElapsedTime = 0;
		float m_MaxTime = 1;
		int m_FPS = 0;
		std::shared_ptr<TextComponent> m_pTextComponent{ nullptr };
		
	};

}

