#pragma once

class SoundService
{
public:
	virtual ~SoundService() = default;
	virtual void QueueAudioClip(const std::string& path) = 0;
};

class Null_SoundManager final : public SoundService
{
	void QueueAudioClip(const std::string& path) override { std::cout << path << "\n"; }
};

class SoundManager final : public SoundService
{
public:
	SoundManager();
	~SoundManager();
	SoundManager(const SoundManager & other) = default;
	SoundManager(SoundManager && other) = default;
	SoundManager& operator=(const SoundManager & other) = default;
	SoundManager& operator=(SoundManager && other) = default;

	void QueueAudioClip(const std::string& path) override;

private:
	class SoundManagerImpl;
	SoundManagerImpl* pImpl;
};

