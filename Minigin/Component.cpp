#include "MiniginPCH.h"
#include "Component.h"


dae::Component::Component(GameObject* gameObject)
	:m_pGameObject{gameObject}, m_IsActive{true}
{
}

void dae::Component::OnCollision(GameObject*)
{
}

void dae::Component::OnEndCollision(GameObject*)
{
}

bool dae::Component::IsActive() const
{
	return m_IsActive;
}

void dae::Component::SetInActive()
{
	m_IsActive = false;
}

void dae::Component::SetActive()
{
	m_IsActive = true;
}


void dae::Component::FixedUpdate(float)
{
}

dae::GameObject* dae::Component::GetGameObject() const
{
	return m_pGameObject;
}
