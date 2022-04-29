#pragma once
#include "SDL_mixer.h"

class AudioClip
{
public:
	AudioClip(const std::string& path);
	~AudioClip();

	void Load();
	bool Play();

	void SetVolume(int volume);
	int GetVolume() const;


private:
	Mix_Chunk* m_pChunk;
	std::string m_Path;

	bool IsLoaded() const;
};

