#include "MiniginPCH.h"
#include "RenderComponent.h"


dae::RenderComponent::RenderComponent(GameObject* gameObject, std::shared_ptr<Texture2D> texture)
	:Component(gameObject), m_Texture(texture), m_SrcRect()
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
			if (m_SrcRect.h <= 0 || m_SrcRect.w <= 0)
			{
				Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
			}
				
			else
			{
				Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, pos.x, pos.y);
			}
		}
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_Texture = texture;
}

float dae::RenderComponent::GetWidth() const
{
	return float(m_Width);
}

float dae::RenderComponent::GetHeight() const
{
	return float(m_Height);
}

void dae::RenderComponent::SetSrcRect(const SDL_Rect& srcRect)
{
	m_SrcRect = srcRect;
}

