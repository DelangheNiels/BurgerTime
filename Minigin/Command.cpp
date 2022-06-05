#include "MiniginPCH.h"
#include "Command.h"

#include "SceneManager.h"



Command::Command(GameObject* gameObject)
	:m_pGameObject{gameObject}
{
}

bool Command::GetCanBeExecutedOnButtonDown() const
{
	return m_CanExecuteOnButtonDown;
}

bool Command::GetCanBeExecutedOnButtonUp() const
{
	return m_CanExecuteOnButtonUp;
}

bool Command::GetCanBeExecutedOnButtonHold() const
{
	return m_CanExecuteOnButtonHold;
}

void Command::SetCanBeExecutedOnButtonDown(bool execute)
{
	m_CanExecuteOnButtonDown = execute;
}

void Command::SetCanBeExecutedOnButtonUp(bool execute)
{
	m_CanExecuteOnButtonUp = execute;
}

void Command::SetCanBeExecutedOnButtonHold(bool execute)
{
	m_CanExecuteOnButtonHold = execute;
}

