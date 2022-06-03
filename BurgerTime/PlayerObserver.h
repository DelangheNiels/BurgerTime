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

	};
}


