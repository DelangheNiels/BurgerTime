#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "imgui_plot.h"
#include <chrono>
#include "GameObject3D.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::RenderImGui()
{
	/*ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();

	ShowExercise1();
	ShowExercise2();
	
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());*/
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::ShowExercise1()
{
	ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	static int samples = 10;
	ImGui::InputInt("# samples", &samples);

	static int clicked = 0;
	if (ImGui::Button("Trash the cache"))
	{
		clicked++;
		
	}
		
	if (clicked & 1)
	{
		if (m_CalculateEx1Plot)
		{
			CalculatePlotEx1(samples);
		}
		ShowPlotEx1();
	}
	ImGui::End();
}

void dae::Renderer::ShowPlotEx1()
{
	
	static ImU32 color = {ImColor(255, 100, 0)};

	static uint32_t selection_start = 0, selection_length = 0;

	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.xs = m_Xdata;
	conf.values.count = m_BufSize;
	conf.values.ys = m_Ydata; // use ys_list to draw several lines simultaneously
	conf.values.ys_count = 1;
	conf.values.color = color;
	conf.scale.min = 1;
	conf.scale.max = 4800;
	conf.tooltip.show = true;
	conf.grid_x.show = true;
	conf.grid_x.size = 124;
	conf.grid_x.subticks = 4;
	conf.grid_y.show = true;
	conf.grid_y.size = 300;
	conf.grid_y.subticks = 4;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(250, 150);
	ImGui::Plot("plot1", conf);
}

void dae::Renderer::CalculatePlotEx1(int samples)
{
	const int bufferSize{ 10000000 };
	int* buffer = new int[bufferSize] {};


	int index = 0;
	for (int i = 1; i <= 1024; i *= 2)
	{
		std::chrono::microseconds total{};
		std::chrono::microseconds smallest{ 1000000 };
		std::chrono::microseconds biggest{ 0 };

		for (int j = 0; j < samples; j++)
		{
			auto start{ std::chrono::high_resolution_clock::now() };

			for (int idx{}; idx < bufferSize; idx += i)
			{
				buffer[idx] *= 2;
			}

			auto end{ std::chrono::high_resolution_clock::now() };

			auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			total += diff;

			if (diff < smallest)
			{
				smallest = diff;
			}

			if (diff > biggest)
			{
				biggest = diff;
			}
		}

		auto toRemove = biggest + smallest;
		total -= toRemove;
		total /= samples - 2;
		m_Ydata[index] = float(total.count());
		++index;
	}
	m_CalculateEx1Plot = false;
}

void dae::Renderer::ShowExercise2()
{
	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	static int samples = 100;
	ImGui::InputInt("# samples", &samples);

	static int clicked2 = 0;
	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
		clicked2++;
	
	}

	if (clicked2 & 1)
	{
		if (m_CalculateGameObjPlot)
		{
			CalculatePlotGameObj(samples);
		}
		ShowPlotGameObj();
	}

	static int clicked3 = 0;
	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		clicked3++;
		
	}

	if (clicked3 & 1)
	{
		if (m_CalculateGameObjPlotAlt)
		{
			CalculatePlotGameObjAlt(samples);
		}
		ShowPlotGameObjAlt();
		ImGui::Text("Combined: ");
		ShowPlotCombined();
	}

	ImGui::End();
}

void dae::Renderer::ShowPlotGameObj()
{
	static ImU32 color = { ImColor(0, 255, 0) };

	static uint32_t selection_start = 0, selection_length = 0;

	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.xs = m_Xdata;
	conf.values.count = m_BufSize;
	conf.values.ys = m_YdataGameObj;
	conf.values.ys_count = 1;
	conf.values.color = color;
	conf.scale.min = 0;
	conf.scale.max = 50000;
	conf.tooltip.show = true;
	conf.grid_x.show = true;
	conf.grid_x.size = 124;
	conf.grid_x.subticks = 1;
	conf.grid_y.show = true;
	conf.grid_y.size = 300;
	conf.grid_y.subticks = 1;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(250, 150);
	ImGui::Plot("plot2", conf);
}

void dae::Renderer::CalculatePlotGameObj(int samples)
{
	const int bufferSize{ 10000000 };
	GameObject3D* objBuffer = new GameObject3D[bufferSize]{};

	int index = 0;

	for (int i = 1; i <= 1024; i *= 2)
	{
		std::chrono::microseconds total{};
		std::chrono::microseconds smallest{ 100000 };
		std::chrono::microseconds biggest{ 0 };


		for (int j = 0; j < samples; ++j)
		{
			auto start{ std::chrono::high_resolution_clock::now() };

			for (int idx{}; idx < bufferSize; idx += i)
			{
				objBuffer[idx].ID *= 2;
			}

			auto end{ std::chrono::high_resolution_clock::now() };

			auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			total += diff;

			if (diff < smallest)
			{
				smallest = diff;
			}

			if (diff > biggest)
			{
				biggest = diff;
			}

		}

		auto toRemove = biggest + smallest;
		total -= toRemove;

		total /= samples - 2;
		m_YdataGameObj[index] = float(total.count());
		++index;
		
	}

	m_CalculateGameObjPlot = false;
}

void dae::Renderer::ShowPlotGameObjAlt()
{
	static ImU32 color = { ImColor(0, 255, 255) };

	static uint32_t selection_start = 0, selection_length = 0;

	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.xs = m_Xdata;
	conf.values.count = m_BufSize;
	conf.values.ys = m_YdataGameObjAlt;
	conf.values.ys_count = 1;
	conf.values.color = color;
	conf.scale.min = 0;
	conf.scale.max = 15000;
	conf.tooltip.show = true;
	conf.grid_x.show = true;
	conf.grid_x.size = 124;
	conf.grid_x.subticks = 1;
	conf.grid_y.show = true;
	conf.grid_y.size = 300;
	conf.grid_y.subticks = 1;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(250, 150);
	ImGui::Plot("plot3", conf);
}

void dae::Renderer::ShowPlotCombined()
{

	static uint32_t selection_start = 0, selection_length = 0;

	static const float* y_data[] = { m_YdataGameObj, m_YdataGameObjAlt};
	static ImU32 colors[2] = { ImColor(0, 255, 0), ImColor(0, 255, 255) };

	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.xs = m_Xdata;
	conf.values.count = m_BufSize;
	conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
	conf.values.ys_count = 2;
	conf.values.colors = colors;
	conf.scale.min = 0;
	conf.scale.max = 50000;
	conf.tooltip.show = true;
	conf.grid_x.show = true;
	conf.grid_x.size = 124;
	conf.grid_x.subticks = 1;
	conf.grid_y.show = true;
	conf.grid_y.size = 300;
	conf.grid_y.subticks = 1;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(250, 150);
	ImGui::Plot("plot4", conf);
}

void dae::Renderer::CalculatePlotGameObjAlt(int samples)
{
	const int bufferSize{ 10000000 };
	GameObject3DAlt* objBufferAlt = new GameObject3DAlt[bufferSize]{};

	int index = 0;

	for (int i = 1; i <= 1024; i *= 2)
	{
		std::chrono::microseconds total{};
		std::chrono::microseconds smallest{ 100000 };
		std::chrono::microseconds biggest{ 0 };


		for (int j = 0; j < samples; ++j)
		{
			auto start{ std::chrono::high_resolution_clock::now() };

			for (int idx{}; idx < bufferSize; idx += i)
			{
				objBufferAlt[idx].ID *= 2;
			}

			auto end{ std::chrono::high_resolution_clock::now() };

			auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			total += diff;

			if (diff < smallest)
			{
				smallest = diff;
			}

			if (diff > biggest)
			{
				biggest = diff;
			}

		}

		auto toRemove = biggest + smallest;
		total -= toRemove;

		total /= samples - 2;
		m_YdataGameObjAlt[index] = float(total.count());
		++index;

	}

	m_CalculateGameObjPlotAlt = false;
}
