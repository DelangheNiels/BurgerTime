#pragma once
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_clearColor{};

		static const size_t m_BufSize = 11;
		float m_Ydata[m_BufSize];
		float m_YdataGameObj[m_BufSize];
		float m_YdataGameObjAlt[m_BufSize];
		float m_Xdata[11]{ 1,2,4,8,16,32,64,128,256,512,1024 };
		bool m_CalculateEx1Plot = true;
		bool m_CalculateGameObjPlot = true;
		bool m_CalculateGameObjPlotAlt = true;

	public:

		void Init(SDL_Window* window);
		void Render() const;
		void RenderImGui();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture,const SDL_Rect& srcRect, float x, float y) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

