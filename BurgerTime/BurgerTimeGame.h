#pragma once
#include "Minigin.h"
class BurgerTimeGame : public dae::Minigin
{
public:
	virtual void LoadGame() const override;
private:
	bool m_Multiplayer{ false };

};

