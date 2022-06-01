#pragma once
#include "Minigin.h"
class BurgerTimeGame : public dae::Minigin
{
public:
	virtual void LoadGame() const override;
private:

	void CreateLevel(dae::Scene& scene) const;
	void CreatePlatform(dae::Scene& scene, float x, float y,const std::string& texture) const;
	void CreateLadder(dae::Scene& scene, float x, float y,const std::string& texture, const std::string& tag = "Ladder") const;
	void CreateBorder(dae::Scene& scene, float x, float y, float width, const std::string& tag) const;

};

