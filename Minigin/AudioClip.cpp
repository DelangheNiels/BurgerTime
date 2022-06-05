#include "MiniginPCH.h"
#include "AudioClip.h"
#include "SDL_mixer.h"


class AudioClip::AudioClipImpl
{
	Mix_Chunk* m_pChunk{};
	std::string m_Path{};
	bool m_Loop{};

public:
	AudioClipImpl(const std::string& path, bool loop = false)
		:m_Path(path), m_Loop{loop}
	{}

	~AudioClipImpl()
	{
		std::cout << "delete in clip" << "\n";
		if (m_pChunk)
			Mix_FreeChunk(m_pChunk);
	}

	void Load()
	{
		m_pChunk = Mix_LoadWAV(m_Path.c_str());
		if (m_pChunk == nullptr)
		{
			std::cout << "could not find path: " << m_Path << "\n";
		}
	}

	bool IsLoaded() const
	{
		if (m_pChunk == nullptr)
			return false;

		return true;
	}

	bool Play()
	{
		if (!IsLoaded())
			return false;

		int channel{};
		if (m_Loop)
		{
			channel = Mix_PlayChannel(-1, m_pChunk, -1);
		}
		
		else
		{
			channel = Mix_PlayChannel(-1, m_pChunk, 0);
		}

		return channel == -1 ? false : true;
	}

	void SetVolume(int volume)
	{
		if (IsLoaded())
		{
			Mix_Volume(-1, volume);
		}
	}

	int GetVolume() const
	{
		if (IsLoaded())
		{
			return Mix_VolumeChunk(m_pChunk, -1);
		}
		return 0;
	}
};

AudioClip::AudioClip(const std::string& path, bool loop)
{
	pImpl = new AudioClipImpl(path, loop);
}

AudioClip::~AudioClip()
{
	delete pImpl;
}

void AudioClip::Load()
{
	pImpl->Load();
}

bool AudioClip::Play()
{
	return pImpl->Play();
}

void AudioClip::SetVolume(int volume)
{
	pImpl->SetVolume(volume);
}

bool AudioClip::IsLoaded() const
{
	return pImpl->IsLoaded();
}

int AudioClip::GetVolume() const
{
	return pImpl->GetVolume();
}

