#pragma once
#include "SoundManager.h"
class ServiceLocator final
{
public:

	ServiceLocator() = default;
	~ServiceLocator();
	ServiceLocator(const ServiceLocator& other) = default;
	ServiceLocator(ServiceLocator && other) = default;
	ServiceLocator& operator=(const ServiceLocator & other) = default;
	ServiceLocator& operator=(ServiceLocator && other) = default;

	static SoundService& GetSoundService();
	static void RegisterSoundService(SoundService* soundService);

private:
	static SoundService* m_SoundServiceInstance;
	static Null_SoundManager m_Default;
};



