#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>
#include "ServiceLocator.h"


HitCommand::HitCommand(GameObject* gameObject)
	:Command(gameObject)
{
}

bool HitCommand::Execute()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->IsDamaged();
	return true;
}

bool QuitCommand::Execute()
{
	std::cout << "Quit" << "\n";
	return false;
}

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


PointsCommand::PointsCommand(GameObject* gameObject)
	:Command(gameObject)
{
}

bool PointsCommand::Execute()
{
	m_pGameObject->GetComponent<PointsComponent>()->IncreasePoints();
	return true;
}

MoveLeftCommand::MoveLeftCommand(GameObject* gameObject)
	:Command(gameObject)
{
	m_CanExecuteOnButtonHold = true;
}

bool MoveLeftCommand::Execute()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->MoveLeft();
	return true;
}

MoveRightCommand::MoveRightCommand(GameObject* gameObject)
	:Command(gameObject)
{
	m_CanExecuteOnButtonHold = true;
}

bool MoveRightCommand::Execute()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->MoveRight();
	return true;
}

MoveUpCommand::MoveUpCommand(GameObject* gameObject)
	:Command(gameObject)
{
	m_CanExecuteOnButtonHold = true;
}

bool MoveUpCommand::Execute()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->MoveUp();
	//ServiceLocator::GetSoundService().QueueAudioClip("../Data/bell.wav");
	return true;
}

MoveDownCommand::MoveDownCommand(GameObject* gameObject)
	:Command(gameObject)
{
	m_CanExecuteOnButtonHold = true;
}

bool MoveDownCommand::Execute()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->MoveDown();
	return true;
}
