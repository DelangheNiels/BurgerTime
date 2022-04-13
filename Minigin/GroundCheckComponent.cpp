#include "MiniginPCH.h"
#include "GroundCheckComponent.h"
#include "RenderComponent.h"

dae::GroundCheckComponent::GroundCheckComponent(GameObject* gameObject)
    :Component(gameObject)
{
}

bool dae::GroundCheckComponent::CheckOnGround(GameObject* otherObject)
{
    int otherObjectWidth = otherObject->GetComponent<RenderComponent>()->GetWidth();
    auto otherObjectPos = otherObject->GetTransform().GetPosition();

    auto characterPos = m_pGameObject->GetTransform().GetPosition();
    int characterWidth = m_pGameObject->GetComponent<RenderComponent>()->GetWidth();
    int characterHeight = m_pGameObject->GetComponent<RenderComponent>()->GetHeight();

    if ((characterPos.x >= otherObjectPos.x && characterPos.x + characterWidth <= otherObjectPos.x + otherObjectWidth) &&
        (characterPos.y + characterHeight >= otherObjectPos.y && characterPos.y + characterHeight <= otherObjectPos.y + 10))
    {
        return true;
    }

    return false;
}

void dae::GroundCheckComponent::Update(float)
{
}
