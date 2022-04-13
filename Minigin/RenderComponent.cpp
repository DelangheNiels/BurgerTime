#include "MiniginPCH.h"
#include "RenderComponent.h"


dae::RenderComponent::RenderComponent(GameObject* gameObject,std::shared_ptr<Texture2D> texture)
	:Component(gameObject), m_Texture(texture)
{
	m_Width = 0;
	m_Height = 0;
	if (m_Texture != nullptr)
	{
		Uint32 format;
		int access;
		SDL_QueryTexture(m_Texture.get()->GetSDLTexture(), &format, &access, &m_Width, &m_Height);
	}
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

int dae::RenderComponent::GetWidth() const
{
	return m_Width;
}

int dae::RenderComponent::GetHeight() const
{
	return m_Height;
}

