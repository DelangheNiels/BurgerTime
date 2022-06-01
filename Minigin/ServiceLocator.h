#pragma once
#include "SoundManager.h"
class ServiceLocator final
{
public:

	ServiceLocator() = delete;
	~ServiceLocator();
	ServiceLocator(const ServiceLocator& other) = delete;
	ServiceLocator(ServiceLocator && other) = delete;
	ServiceLocator& operator=(const ServiceLocator & other) = delete;
	ServiceLocator& operator=(ServiceLocator && other) = delete;

	static SoundService& GetSoundService();
	static void RegisterSoundService(SoundService* soundService);

	static void ShutDown();

private:
	static SoundService* m_SoundServiceInstance;
	static Null_SoundManager m_Default;
};



