#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>
#include "..\BurgerTime\PeterPeperComponent.h"

dae::GameObject::~GameObject()
{
	delete m_pParent;
}

void dae::GameObject::AddComponent(const std::shared_ptr<Component>&component)
{
	if (component.get()->GetGameObject() == this)
	{
		m_Components.push_back(component);
	}
	
}

std::shared_ptr<dae::Component> dae::GameObject::GetComponentAtindex(int index)
{
	return m_Components.at(index);
}

void dae::GameObject::SetParent(GameObject* parent)
{
	if (parent)
	{
		if (this != parent)
		{
			if (this->Getparent() != nullptr)
			{
				m_pParent->RemoveChild(this);
			}

			m_pParent = parent;
			parent->AddChild(this);
		}
	}

	else
	{
		m_pParent->RemoveChild(this);

		m_pParent = nullptr;
	}
	
}

dae::GameObject* dae::GameObject::Getparent() const
{
	return m_pParent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Children.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	return m_Children.at(index);
}

void dae::GameObject::RemoveChild(GameObject* gameObject)
{
	auto it = std::find(m_Children.begin(), m_Children.end(), gameObject);
	int index = int(it - m_Children.begin());

	auto child = m_Children.at(index);
	child->SetParent(nullptr);
	m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
	
	//reset relative position to world position
	child->SetRelativePosition(child->GetTransform().GetPosition().x, child->GetTransform().GetPosition().y);

}

void dae::GameObject::AddChild(GameObject* gameObject)
{
	if (gameObject && gameObject != this)
	{
		if (gameObject->Getparent() != nullptr)
		{
			gameObject->Getparent()->RemoveChild(gameObject);

		}

		//set transform relative to the parent

		gameObject->SetParent(this);
		m_Children.push_back(gameObject);
		auto relativePos = gameObject->GetTransform().GetPosition() - GetTransform().GetPosition();
		gameObject->SetRelativePosition(relativePos.x, relativePos.y);
	}
	
}

void dae::GameObject::OnCollision(GameObject* pOther)
{
	for (auto& component : m_Components)
	{
		if(component.get()->IsActive())
			component.get()->OnCollision(pOther);
	}
}

void dae::GameObject::OnEndCollision(GameObject* pOther)
{
	for (auto& component : m_Components)
	{
		if (component.get()->IsActive())
			component.get()->OnEndCollision(pOther);
	}
}

void dae::GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

std::string dae::GameObject::GetTag() const
{
	return m_Tag;
}

void dae::GameObject::SetPosition(float x, float y)
{
	auto oldPos = m_Transform.GetPosition();
	m_Transform.SetPosition(x, y, 0.0f);

	auto difference = m_Transform.GetPosition() - oldPos;

	for (size_t i = 0; i < m_Children.size(); i++)
	{
		auto newPos = m_Children[i]->GetTransform().GetPosition() + difference;
		m_Children[i]->SetPosition(newPos.x, newPos.y);
	}
}

void dae::GameObject::SetRelativePosition(float x, float y)
{
	m_LocalTransform.SetPosition(x, y, 1);
}

dae::Transform dae::GameObject::GetTransform() const
{
	return m_Transform;
}

dae::Transform dae::GameObject::GetLocalTransfrom() const
{
	return m_LocalTransform;
}

void dae::GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		if(m_Components[i].get()->IsActive())
			m_Components[i].get()->Update(deltaTime);
	}

	for (size_t i = 0; i < m_Children.size(); i++)
	{
		m_Children[i]->Update(deltaTime);
	}
}

void dae::GameObject::FixedUpdate(float fixedTime)
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		if (m_Components[i].get()->IsActive())
			m_Components[i].get()->FixedUpdate(fixedTime);
	}

	for (size_t i = 0; i < m_Children.size(); i++)
	{
		m_Children[i]->FixedUpdate(fixedTime);
	}
}
