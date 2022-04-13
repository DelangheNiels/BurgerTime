#pragma once
#include "Component.h"
#include "Transform.h"
#include <string>

namespace dae
{
	class Font;
	class Texture2D;
	class RenderComponent;
	class TextComponent final : public Component
	{
	public:
		void Update(float deltaTime) override;

		void SetText(const std::string& text);
		//void SetPosition(float x, float y);

		explicit TextComponent(GameObject* gameObject,const std::string& text, const std::shared_ptr<Font>& font,const std::shared_ptr<RenderComponent>& renderComponent , const SDL_Color& color = { 255,255,255 });
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<dae::Texture2D> m_Texture{};
		std::shared_ptr<RenderComponent> m_pRenderComponent{ nullptr };
		SDL_Color m_Color;
	};
}
