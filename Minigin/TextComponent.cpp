#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent(GameObject* gameObject,const std::string& text,const std::shared_ptr<Font>& font,const std::shared_ptr<RenderComponent>& renderComponent,const SDL_Color& color)
	: Component(gameObject), m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr),m_pRenderComponent(renderComponent), m_Color(color)
{ }

void dae::TextComponent::Update(float )
{
	if (m_NeedsUpdate)
	{
		//const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
	
		m_pRenderComponent.get()->SetTexture(std::make_shared<Texture2D>(texture));
		m_NeedsUpdate = false;
	}
}


// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

//void dae::TextComponent::SetPosition(const float x, const float y)
//{
//	m_Transform.SetPosition(x, y, 0.0f);
//}


