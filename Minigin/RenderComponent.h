#pragma once

#include "Component.h"
#include "Texture2D.h"
#include "Renderer.h"
namespace dae
{
	class RenderComponent final : public Component
	{
	public:
		void Update(float deltaTime) override;
		void Render() const;
		void SetTexture(const std::shared_ptr<Texture2D>& texture);

		explicit RenderComponent(GameObject* gameObject, std::shared_ptr<Texture2D> texture);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent & other) = delete;
		RenderComponent(RenderComponent && other) = delete;
		RenderComponent& operator=(const RenderComponent & other) = delete;
		RenderComponent& operator=(RenderComponent && other) = delete;

	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}


