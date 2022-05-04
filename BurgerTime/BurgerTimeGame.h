#pragma once
#include "Minigin.h"
class BurgerTimeGame : public dae::Minigin
{
public:
	virtual void LoadGame() const override;
private:

	void CreateLevel(dae::Scene& scene) const;
	void CreatePlatform(dae::Scene& scene, float x, float y, std::string texture) const;
	void CreateLadder(dae::Scene& scene, float x, float y, std::string texture) const;

};

