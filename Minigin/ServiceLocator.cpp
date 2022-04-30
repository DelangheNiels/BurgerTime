#include "MiniginPCH.h"
#include "ServiceLocator.h"

SoundService* ServiceLocator::m_SoundServiceInstance{};
Null_SoundManager ServiceLocator::m_Default{};

ServiceLocator::~ServiceLocator()
{
	std::cout << "in destructor" << "\n";
	delete m_SoundServiceInstance;
}

SoundService& ServiceLocator::GetSoundService()
{
	return *m_SoundServiceInstance;
}

void ServiceLocator::RegisterSoundService(SoundService* soundService)
{
	if (m_SoundServiceInstance != &m_Default)
	{
		std::cout << "delete in service" << "\n";
		delete m_SoundServiceInstance;
		m_SoundServiceInstance = nullptr;
	}
	m_SoundServiceInstance = soundService == nullptr ? &m_Default : soundService;
}

