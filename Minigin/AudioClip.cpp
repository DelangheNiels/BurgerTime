#include "MiniginPCH.h"
#include "AudioClip.h"

AudioClip::AudioClip(const std::string& path)
	:m_Path(path)
{
}

AudioClip::~AudioClip()
{
	if (m_pChunk)
		Mix_FreeChunk(m_pChunk);
}

void AudioClip::Load()
{
	m_pChunk = Mix_LoadWAV(m_Path.c_str());
	if (m_pChunk == nullptr)
	{
		std::cout << "could not find path: " << m_Path << "\n";
	}
}

bool AudioClip::Play()
{
	if (!IsLoaded())
		return false;

	int channel = Mix_PlayChannel(-1, m_pChunk, 0);
	return channel == -1 ? false : true;
}

void AudioClip::SetVolume(int volume)
{
	if (IsLoaded())
	{
		Mix_Volume(-1, volume);
	}
}

bool AudioClip::IsLoaded() const
{
	if (m_pChunk == nullptr)
		return false;

	return true;
}

int AudioClip::GetVolume() const
{
	if (IsLoaded())
	{
		Mix_VolumeChunk(m_pChunk, -1);
	}
	return 0;
}

