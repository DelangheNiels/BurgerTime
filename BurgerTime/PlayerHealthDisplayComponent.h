#pragma once
#include "PlayerObserver.h"
#include "../BurgerTime/PeterPeperComponent.h"
#include "TextComponent.h"
#include <memory.h>
namespace dae
{
	class PeterPeperComponent;

	class PlayerHealthDisplayComponent final : public PlayerObserver, public Component
	{
	public:

		explicit PlayerHealthDisplayComponent(GameObject* gameObject,PeterPeperComponent* player ,const std::shared_ptr<TextComponent>& textComponent);
		virtual ~PlayerHealthDisplayComponent() = default;

		void IsDead() override;
		void TookDamage() override;

		void Update(float deltaTime) override;

		void SetObservedPlayer(PeterPeperComponent* player);
		void printPlayer();

	private:

		PeterPeperComponent* m_pObservedPlayer;
		std::shared_ptr<TextComponent> m_pTextComponent{};
		
	};

}

