#pragma once

class AudioClip final
{
public:
	AudioClip(const std::string& path);
	~AudioClip();

	void Load();
	bool Play();

	void SetVolume(int volume);
	int GetVolume() const;
	bool IsLoaded() const;


private:

	class AudioClipImpl;
	AudioClipImpl* pImpl{};
};

