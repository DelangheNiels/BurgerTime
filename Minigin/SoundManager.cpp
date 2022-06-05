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
	std::condition_variable m_WaitingCondition;

	void LoopOverQueue()
	{
		while (m_Continue)
		{
			std::unique_lock lk{ mutex };
			m_WaitingCondition.wait(lk, [&]{ return !m_AudioQueue.empty() || !m_Continue;});

			if (m_AudioQueue.size() > 0)
			{
				
				AudioClip* clip = m_AudioQueue.front();
				m_ClipsToDelete.emplace_back(m_AudioQueue.front());
				m_AudioQueue.pop();

				lk.unlock();
				
				std::cout << m_AudioQueue.size() << "\n";
				clip->Load();
				clip->Play();
				
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
		m_WaitingCondition.notify_all();
		queueThread.join();
		for (size_t i = 0; i < m_ClipsToDelete.size(); i++)
		{
			
			delete m_ClipsToDelete[i];
		}

		for (size_t i = 0; i < m_AudioQueue.size(); i++)
		{
			m_AudioQueue.pop();
		}
		Mix_CloseAudio();
	}

	void QueueAudioClip(const std::string& path, float volume ,bool loop)
	{
		mutex.lock();
		m_AudioQueue.emplace(new AudioClip(path, volume,loop));
		mutex.unlock();
		m_WaitingCondition.notify_all();
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

void SoundManager::QueueAudioClip(const std::string& path, float volume ,bool loop)
{
	pImpl->QueueAudioClip(path, volume,loop);
}
