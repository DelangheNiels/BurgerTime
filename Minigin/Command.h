#pragma once
#include "../BurgerTime/PeterPeperComponent.h"
#include "../BurgerTime/PointsComponent.h"
#include "GameObject.h"
using namespace dae;

class Command
{
public:
	Command(GameObject* gameObject);
	virtual ~Command() = default;
	virtual bool Execute() = 0;

	bool GetCanBeExecutedOnButtonDown() const;
	bool GetCanBeExecutedOnButtonUp() const;
	bool GetCanBeExecutedOnButtonHold() const;

	void SetCanBeExecutedOnButtonDown(bool execute);
	void SetCanBeExecutedOnButtonUp(bool execute);
	void SetCanBeExecutedOnButtonHold(bool execute);

protected:
	GameObject* m_pGameObject;
	bool m_CanExecuteOnButtonHold = false;

private:
	bool m_CanExecuteOnButtonDown = true;
	bool m_CanExecuteOnButtonUp = false;

	
};

class HitCommand final : public Command
{
public:
	HitCommand(GameObject* gameObject);
	bool Execute() override;

private:
	
};

class PointsCommand final : public Command
{
public:
	PointsCommand(GameObject* gameObject);
	bool Execute() override;

private:

};

class QuitCommand final :public Command
{
public:
	bool Execute() override;
};

class MoveLeftCommand final : public Command
{
public:
	MoveLeftCommand(GameObject* gameObject);
	bool Execute() override;
};

class MoveRightCommand final : public Command
{
public:
	MoveRightCommand(GameObject* gameObject);
	bool Execute() override;
};

class MoveUpCommand final : public Command
{
public:
	MoveUpCommand(GameObject* gameObject);
	bool Execute() override;
};

class MoveDownCommand final : public Command
{
public:
	MoveDownCommand(GameObject* gameObject);
	bool Execute() override;
};

