#pragma once
#include "Component.h"

namespace dae
{

	class PlayerObserver
	{
	public:
		virtual ~PlayerObserver() = default;
		virtual void IsDead() = 0;
		virtual void TookDamage() = 0;


		//health display component erft over van playerObserver
		//display heeft speler, dan kan hij zich adden/removen van de player
	};
}


