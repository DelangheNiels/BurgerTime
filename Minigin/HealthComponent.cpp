#include "MiniginPCH.h"
#include "HealthComponent.h"

void dae::HealthComponent::Update(float)
{
}

dae::HealthComponent::HealthComponent(GameObject* gameObject, const std::shared_ptr<TextComponent>& textComponent)
	:Component(gameObject), m_TextComponent(textComponent), m_Health{ 3 }
{
}
