#pragma once

#include "Component.h"


namespace dae
{
	class RenderComponent;

	class AnimatedSpriteComponent final : public Component
	{
	public:
		explicit AnimatedSpriteComponent(GameObject* gameObject, RenderComponent* renderComp, int amountOfAnimations, const std::string& spriteSheet);
		virtual ~AnimatedSpriteComponent() = default;
		AnimatedSpriteComponent(const AnimatedSpriteComponent& other) = delete;
		AnimatedSpriteComponent(AnimatedSpriteComponent&& other) = delete;
		AnimatedSpriteComponent& operator=(const AnimatedSpriteComponent& other) = delete;
		AnimatedSpriteComponent& operator=(AnimatedSpriteComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Reset();
		void Activate();

		float GetChangeImageTime() const;
		int GetAmountOfAnimations() const;
		std::string GetSpriteSheet() const;
		

	private:
		int m_AmountOfAnimations;
		RenderComponent* m_pRenderComponent;
		float m_ChangeImageTime = 0.4f;
		float m_ChangeImageTimer = m_ChangeImageTime;
		int m_CurrentSpriteIndex = 0;
		float m_SrRectWidth, m_SrcRectHeight;

		std::string m_SpriteSheet;

		bool m_isActive;
	};
};


