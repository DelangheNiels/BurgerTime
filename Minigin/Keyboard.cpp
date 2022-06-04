#include "MiniginPCH.h"
#include "Keyboard.h"

dae::Keyboard::Keyboard()
{
	m_pNumberOfKeys = new int();
	m_pCurrentState = SDL_GetKeyboardState(m_pNumberOfKeys);
	m_pPreviousState = new UINT8[*m_pNumberOfKeys];
}

dae::Keyboard::~Keyboard()
{
	/*delete m_pCurrentState;
	m_pCurrentState = nullptr;*/

	delete m_pPreviousState;
	m_pPreviousState = nullptr;

	delete m_pNumberOfKeys;
	m_pNumberOfKeys = nullptr;
}

void dae::Keyboard::Update()
{
	std::memcpy(m_pPreviousState, m_pCurrentState, *m_pNumberOfKeys);
	m_FirstFrameDone = true;
}

bool dae::Keyboard::IsPressed(unsigned int key)
{
	if (m_pCurrentState[key] && m_FirstFrameDone)
	{
		return true;
	}
	
	return false;
}

bool dae::Keyboard::IsDowThisFrame(unsigned int key)
{
	if (m_pCurrentState[key] && !m_pPreviousState[key] && m_FirstFrameDone)
	{
		return true;
	}
	return false;
}

bool dae::Keyboard::IsUpThisFrame(unsigned int key)
{

	if (!m_pCurrentState[key] && m_pPreviousState[key] && m_FirstFrameDone)
	{
		return true;
	}

	return false;
}
