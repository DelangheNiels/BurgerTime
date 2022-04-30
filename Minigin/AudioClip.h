#pragma once

class AudioClip final
{
public:
	AudioClip(const std::string& path);
	~AudioClip();

	AudioClip(const AudioClip & other) = default;
	AudioClip(AudioClip && other) = default;
	AudioClip& operator=(const AudioClip & other) = default;
	AudioClip& operator=(AudioClip && other) = default;

	void Load();
	bool Play();

	void SetVolume(int volume);
	int GetVolume() const;
	bool IsLoaded() const;


private:

	class AudioClipImpl;
	AudioClipImpl* pImpl{};
};

