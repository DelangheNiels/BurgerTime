#include "MiniginPCH.h"
#include "AnimatedSpriteComponent.h"
#include "RenderComponent.h"



dae::AnimatedSpriteComponent::AnimatedSpriteComponent(GameObject* gameObject, RenderComponent* renderComp, int amountOfAnimations, const std::string& spriteSheet)
	:Component(gameObject), m_pRenderComponent(renderComp), m_AmountOfAnimations(amountOfAnimations), m_SpriteSheet(spriteSheet), m_isActive(false)
{
	m_SrRectWidth = m_pRenderComponent->GetWidth();
	m_SrcRectHeight = m_pRenderComponent->GetHeight();
}

void dae::AnimatedSpriteComponent::Update(float deltaTime)
{
	if (m_isActive)
	{
		m_ChangeImageTimer += deltaTime;

		if (m_ChangeImageTimer >= m_ChangeImageTime)
		{
			++m_CurrentSpriteIndex;
			m_ChangeImageTimer = 0.0f;
			if (m_CurrentSpriteIndex == m_AmountOfAnimations)
			{
				m_CurrentSpriteIndex = 0;
			}

			SDL_Rect srcRect;
			srcRect.w = int(m_SrRectWidth);
			srcRect.h = int(m_SrcRectHeight);
			srcRect.x = int(m_SrRectWidth * m_CurrentSpriteIndex);
			srcRect.y = 0;
			m_pRenderComponent->SetSrcRect(srcRect);

		}
	}
	
}

void dae::AnimatedSpriteComponent::Reset()
{
	m_CurrentSpriteIndex = 0;
	m_ChangeImageTimer = m_ChangeImageTime;
	m_isActive = false;
}

void dae::AnimatedSpriteComponent::Activate()
{
	m_isActive = true;
}

std::string dae::AnimatedSpriteComponent::GetSpriteSheet() const
{
	return m_SpriteSheet;
}
