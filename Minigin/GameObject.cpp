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
	if (this != parent)
	{
		if (this->Getparent() != nullptr)
		{
			//remove this child from old parent
			auto it = std::find(m_pParent->m_Children.begin(), m_pParent->m_Children.end(), this);
			if (it != m_pParent->m_Children.end())
			{
				int index =int( it - m_pParent->m_Children.begin());
				m_pParent->RemoveChild(index);
			}

		}

		m_pParent = parent;
		parent->AddChild(this);

		//set transform relative to the parent
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

void dae::GameObject::RemoveChild(int index)
{

	m_Children.at(index)->SetParent(nullptr);
	m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), m_Children.at(index)), m_Children.end());

	//update location, rotation and scale
}

void dae::GameObject::AddChild(GameObject* gameObject)
{
	if (gameObject->Getparent() != nullptr)
	{
		//remove child from parent
		
	}

	//set transform relative to the parent

	gameObject->SetParent(this);
	m_Children.push_back(gameObject);
}

void dae::GameObject::OnCollision(GameObject* pOther)
{
	for (auto& component : m_Components)
	{
		component.get()->OnCollision(pOther);
	}
}

void dae::GameObject::OnEndCollision(GameObject* pOther)
{
	for (auto& component : m_Components)
	{
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
	m_Transform.SetPosition(x, y, 0.0f);
}

dae::Transform dae::GameObject::GetTransform() const
{
	return m_Transform;
}

void dae::GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
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
		m_Components[i].get()->FixedUpdate(fixedTime);
	}

	for (size_t i = 0; i < m_Children.size(); i++)
	{
		m_Children[i]->FixedUpdate(fixedTime);
	}
}

//add and remove child is not needed, can do everything in setParent
// make them private ad use them in set parent to get the same result
//add bool to setParent to keep worldposition or not
//have 2 positions, local and world position, no parent -> world space = local space