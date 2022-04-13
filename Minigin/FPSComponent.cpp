#include "MiniginPCH.h"
#include "FPSComponent.h"
#include <chrono>
#include "TextComponent.h"
dae::FPSComponent::FPSComponent(GameObject* gameObject,const std::shared_ptr<TextComponent>& textComponent)
	:Component(gameObject), m_pTextComponent(textComponent)
{
    
}

void dae::FPSComponent::Update(float deltaTime)
{

    m_FPS++;

    m_ElapsedTime += deltaTime;

    if (m_ElapsedTime >= m_MaxTime) {
       
        //m_pGameObject->GetComponent<TextComponent>()->SetText("FPS: " + std::to_string(m_FPS));
        m_pTextComponent.get()->SetText("FPS: " + std::to_string(m_FPS));
        m_ElapsedTime = 0;
        m_FPS = 0;

    }
}



