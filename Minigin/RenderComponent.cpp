#include "MiniginPCH.h"
#include "RenderComponent.h"


dae::RenderComponent::RenderComponent(GameObject* gameObject,std::shared_ptr<Texture2D> texture)
	:Component(gameObject), m_Texture(texture)
{
}

void dae::RenderComponent::Update( float )
{
	
}

void dae::RenderComponent::Render() const
{
	if (m_Texture != nullptr)
		{
			const auto& pos = m_pGameObject->GetTransform().GetPosition();
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
		}
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_Texture = texture;
}

