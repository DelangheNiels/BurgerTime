#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>
#include "ServiceLocator.h"


HitCommand::HitCommand(GameObject* gameObject)
	:Command(gameObject)
{
}

bool HitCommand::ExecuteOnHold()
{
	return true;
}

bool HitCommand::ExecuteOnDown()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->IsDamaged();
	return true;
}

bool HitCommand::ExecuteOnUp()
{
	return true;
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

bool PointsCommand::ExecuteOnHold()
{
	return true;
}

bool PointsCommand::ExecuteOnDown()
{
	m_pGameObject->GetComponent<PointsComponent>()->PartDropped();
	return true;
}

bool PointsCommand::ExecuteOnUp()
{
	return true;
}

MoveLeftCommand::MoveLeftCommand(GameObject* gameObject)
	:Command(gameObject)
{
	m_CanExecuteOnButtonHold = true;
	m_CanExecuteOnButtonUp = true;
}

bool MoveLeftCommand::ExecuteOnHold()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->MoveLeft();
	return true;
}

bool MoveLeftCommand::ExecuteOnDown()
{
	return true;
}

bool MoveLeftCommand::ExecuteOnUp()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->StopMoveLeft();
	return true;
}

MoveRightCommand::MoveRightCommand(GameObject* gameObject)
	:Command(gameObject)
{
	m_CanExecuteOnButtonHold = true;
	m_CanExecuteOnButtonUp = true;
}

bool MoveRightCommand::ExecuteOnHold()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->MoveRight();
	return true;
}

bool MoveRightCommand::ExecuteOnDown()
{
	return true;
}

bool MoveRightCommand::ExecuteOnUp()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->StopMoveRight();
	return true;
}

MoveUpCommand::MoveUpCommand(GameObject* gameObject)
	:Command(gameObject)
{
	m_CanExecuteOnButtonHold = true;
	m_CanExecuteOnButtonUp = true;
}

bool MoveUpCommand::ExecuteOnHold()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->MoveUp();
	//ServiceLocator::GetSoundService().QueueAudioClip("../Data/bell.wav");
	return true;
}

bool MoveUpCommand::ExecuteOnDown()
{
	return true;
}

bool MoveUpCommand::ExecuteOnUp()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->StopMoveUp();
	//ServiceLocator::GetSoundService().QueueAudioClip("../Data/bell.wav");
	return true;
}


MoveDownCommand::MoveDownCommand(GameObject* gameObject)
	:Command(gameObject)
{
	m_CanExecuteOnButtonHold = true;
	m_CanExecuteOnButtonUp = true;
}

bool MoveDownCommand::ExecuteOnHold()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->MoveDown();
	return true;
}

bool MoveDownCommand::ExecuteOnDown()
{
	return true;
}

bool MoveDownCommand::ExecuteOnUp()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->StopMoveDown();
	return true;
}


bool QuitCommand::ExecuteOnHold()
{
	return false;
}

bool QuitCommand::ExecuteOnDown()
{
	std::cout << "Quit" << "\n";
	return false;
}

bool QuitCommand::ExecuteOnUp()
{
	return false;
}
