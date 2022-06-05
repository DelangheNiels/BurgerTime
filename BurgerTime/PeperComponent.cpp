#include "BurgerTimePCH.h"
#include "PeperComponent.h"

dae::PeperComponent::PeperComponent(GameObject* gameObject, RenderComponent* renderComp, std::map<PlayerStates, AnimatedSpriteComponent*> animations)
	:Component(gameObject), m_pRenderComponent{renderComp}, m_Animations{animations}
{
}

void dae::PeperComponent::Update(float)
{
}

void dae::PeperComponent::OnCollision(GameObject*)
{
}
