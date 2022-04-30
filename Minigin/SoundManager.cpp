#include "MiniginPCH.h"
#include "SoundManager.h"
#include "SDL_mixer.h"
#include <thread>
#include <queue>
#include "AudioClip.h"
#include <mutex>
#include <vector>

class SoundManager::SoundManagerImpl
{
private:
	std::queue<AudioClip*> m_AudioQueue{};
	std::vector<AudioClip*> m_ClipsToDelete{};
	std::mutex mutex;
	std::thread queueThread;
	bool m_Continue = true;

	void LoopOverQueue()
	{
		while (m_Continue)
		{
			if (m_AudioQueue.size() > 0)
			{
				mutex.lock();
				
				m_AudioQueue.front()->Load();
				m_AudioQueue.front()->Play();
				
				m_ClipsToDelete.emplace_back(m_AudioQueue.front());
				m_AudioQueue.pop();
				mutex.unlock();
				
			}
			
		}
	}


public:
	SoundManagerImpl()
	{
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_CHANNELS);
		queueThread = std::thread([this] { this->LoopOverQueue(); });
		
	}

	~SoundManagerImpl()
	{
		std::cout << "delete in manager" << "\n";
		m_Continue = false;
		queueThread.join();
		for (size_t i = 0; i < m_ClipsToDelete.size(); i++)
		{
			
			delete m_ClipsToDelete[i];
		}
		Mix_CloseAudio();
	}

	void QueueAudioClip(const std::string& path)
	{
		m_AudioQueue.emplace(new AudioClip(path));
	}


};

SoundManager::SoundManager()
{
	
	pImpl = new SoundManagerImpl;
}

SoundManager::~SoundManager()
{
	delete pImpl;
}

void SoundManager::QueueAudioClip(const std::string& path)
{
	pImpl->QueueAudioClip(path);
}
