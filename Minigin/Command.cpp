#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>


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

void Command::SetCanBeExecutedOnButtonDown(bool execute)
{
	m_CanExecuteOnButtonDown = execute;
}

void Command::SetCanBeExecutedOnButtonUp(bool execute)
{
	m_CanExecuteOnButtonUp = execute;
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
}

bool MoveLeftCommand::Execute()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->MoveLeft();
	return true;
}

MoveRightCommand::MoveRightCommand(GameObject* gameObject)
	:Command(gameObject)
{
}

bool MoveRightCommand::Execute()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->MoveRight();
	return true;
}
