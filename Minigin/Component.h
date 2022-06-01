#pragma once
#include "GameObject.h"

namespace dae
{
	class GameObject;
	class Component
	{
	public:
		virtual void Update( float deltaTime) = 0;
		virtual void FixedUpdate(float fixedTime);

		GameObject* GetGameObject() const;

		explicit Component(GameObject* gameObject);
		virtual ~Component() = default;
		Component(const Component & other) = delete;
		Component(Component && other) = delete;
		Component& operator=(const Component & other) = delete;
		Component& operator=(Component && other) = delete;

		virtual void OnCollision(GameObject* gameObject);
		virtual void OnEndCollision(GameObject* gameObject);

	protected:
		GameObject* m_pGameObject{};



	};


}


