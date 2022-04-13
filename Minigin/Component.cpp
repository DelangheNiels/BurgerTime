#include "MiniginPCH.h"
#include "Component.h"


dae::Component::Component(GameObject* gameObject)
	:m_pGameObject{gameObject}
{
}

dae::GameObject* dae::Component::GetGameObject() const
{
	return m_pGameObject;
}
