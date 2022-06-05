#include "BurgerTimePCH.h"
#include "GameCommands.h"

#include "SceneManager.h"

#include "HighscoreManager.h"

QuitCommand::QuitCommand(GameObject* gameObject)
	:Command(gameObject)
{
}

bool QuitCommand::ExecuteOnHold()
{
	return false;
}

bool QuitCommand::ExecuteOnUp()
{
	HighscoreManager::GetInstance().SaveScore();
	return false;
}

bool QuitCommand::ExecuteOnDown()
{
	return false;
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

bool MoveLeftCommand::ExecuteOnUp()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->StopMoveLeft();
	return true;
}

bool MoveLeftCommand::ExecuteOnDown()
{
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

bool MoveRightCommand::ExecuteOnUp()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->StopMoveRight();
	return true;
}

bool MoveRightCommand::ExecuteOnDown()
{
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
	return true;
}

bool MoveUpCommand::ExecuteOnUp()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->StopMoveUp();
	return true;
}

bool MoveUpCommand::ExecuteOnDown()
{
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

bool MoveDownCommand::ExecuteOnUp()
{
	m_pGameObject->GetComponent<PeterPeperComponent>()->StopMoveDown();
	return true;
}

bool MoveDownCommand::ExecuteOnDown()
{
	return true;
}

SelectSinglePlayerCommand::SelectSinglePlayerCommand(GameObject* gameObject)
	:Command(gameObject)
{
}

bool SelectSinglePlayerCommand::ExecuteOnHold()
{
	return true;
}

bool SelectSinglePlayerCommand::ExecuteOnUp()
{
	return true;
}

bool SelectSinglePlayerCommand::ExecuteOnDown()
{
	SceneManager::GetInstance().LoadScene("SinglePlayerGame");
	return true;
}

SelectMultiPlayerCommand::SelectMultiPlayerCommand(GameObject* gameObject)
	:Command(gameObject)
{
}

bool SelectMultiPlayerCommand::ExecuteOnHold()
{
	return true;
}

bool SelectMultiPlayerCommand::ExecuteOnUp()
{
	return true;
}

bool SelectMultiPlayerCommand::ExecuteOnDown()
{
	SceneManager::GetInstance().LoadScene("MultiPlayerGame");
	return true;
}
