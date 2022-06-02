#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"
#include <type_traits>
#include <algorithm>

namespace dae
{
	class Texture2D;
	class Component;
	class GameObject final
	{
	public:

		void SetPosition(float x, float y);
		void SetRelativePosition(float x, float y);

		Transform GetTransform() const;
		Transform GetLocalTransfrom() const;
		void Update(float deltaTime);
		void FixedUpdate(float fixedTime);

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(const std::shared_ptr<Component>& component);
		template <typename Comp> Comp* GetComponent() const;
		
		//mss verwijderen
		std::shared_ptr<Component> GetComponentAtindex(int index);

		void SetParent(GameObject* parent);
		GameObject* Getparent() const;

		size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;
		void RemoveChild(GameObject* gameObject);
		void AddChild(GameObject* gameObject);

		void OnCollision(GameObject* pOther);
		void OnEndCollision(GameObject* pOther);

		void SetTag(const std::string& tag);
		std::string GetTag() const;

	private:
		Transform m_Transform{};
		Transform m_LocalTransform{};
		std::vector <std::shared_ptr<Component>> m_Components{};

		GameObject* m_pParent{ nullptr };
		
		std::vector<GameObject* > m_Children{};

		std::string m_Tag;

	};


	template<typename Comp>
	inline Comp* GameObject::GetComponent() const
	{
		Comp* result = nullptr;
		const auto count = m_Components.size();
		for (unsigned int i = 0; i < count && !result; ++i)
		{
			result = dynamic_cast<Comp*>(m_Components[i].get());
		}
		return result;
	}
}
