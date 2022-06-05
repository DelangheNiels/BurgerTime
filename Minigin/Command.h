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
	virtual bool ExecuteOnHold() = 0;
	virtual bool ExecuteOnUp() = 0;
	virtual bool ExecuteOnDown() = 0;

	bool GetCanBeExecutedOnButtonDown() const;
	bool GetCanBeExecutedOnButtonUp() const;
	bool GetCanBeExecutedOnButtonHold() const;

	void SetCanBeExecutedOnButtonDown(bool execute);
	void SetCanBeExecutedOnButtonUp(bool execute);
	void SetCanBeExecutedOnButtonHold(bool execute);

protected:
	GameObject* m_pGameObject;
	bool m_CanExecuteOnButtonHold = false;
	bool m_CanExecuteOnButtonDown = true;
	bool m_CanExecuteOnButtonUp = false;

private:
	

	
};


