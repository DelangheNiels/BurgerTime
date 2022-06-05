#pragma once


namespace dae
{
	class Scene;

	class LevelLoader final
	{
	public:
		LevelLoader(const std::string& filename);
		virtual ~LevelLoader() = default;
		LevelLoader(const LevelLoader& other) = default;
		LevelLoader(LevelLoader&& other) = default;
		LevelLoader& operator=(const LevelLoader& other) = default;
		LevelLoader& operator=(LevelLoader&& other) = default;

		void LoadLevel(Scene& scene);

	private:
		std::string m_Inputfile;
	};
}


