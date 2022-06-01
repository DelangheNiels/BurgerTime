#include "MiniginPCH.h"
#include "Component.h"


dae::Component::Component(GameObject* gameObject)
	:m_pGameObject{gameObject}
{
}

void dae::Component::OnCollision(GameObject*)
{
}

void dae::Component::OnEndCollision(GameObject*)
{
}


void dae::Component::FixedUpdate(float)
{
}

dae::GameObject* dae::Component::GetGameObject() const
{
	return m_pGameObject;
}
