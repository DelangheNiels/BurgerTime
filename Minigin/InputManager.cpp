#include "MiniginPCH.h"
#include "InputManager.h"
#include "imgui_impl_sdl.h"
#include <algorithm>




InputManager::~InputManager()
{
	for (size_t i = 0; i < m_Controllers.size(); i++)
	{
		delete m_Controllers[i];
	}
}

bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	for (size_t i = 0; i < m_Controllers.size(); i++)
	{
		m_Controllers[i]->Update();
	}
	
	for (size_t i = 0; i < m_Controllers.size(); i++)
	{
		for (std::map<ControllerButton, std::pair<std::unique_ptr<Command>,int>>::iterator iter = m_ControllerCommandsMap.begin(); iter != m_ControllerCommandsMap.end(); ++iter)
		{

			if (IsPressed(iter->first, m_Controllers[i]))
			{
				if (iter->second.first.get()->GetCanBeExecutedOnButtonHold())
				{
					if (i == unsigned(iter->second.second))
					{
						return iter->second.first.get()->ExecuteOnHold();
					}

				}
			}

			if (IsDownThisFrame(iter->first, m_Controllers[i]))
			{
				if (iter->second.first.get()->GetCanBeExecutedOnButtonDown())
				{
					if (i == unsigned(iter->second.second))
					{
						return iter->second.first.get()->ExecuteOnDown();
					}
					
				}

			}

			if (IsUpThisFrame(iter->first, m_Controllers[i]))
			{
				if (iter->second.first.get()->GetCanBeExecutedOnButtonUp())
				{
					if (i == unsigned(iter->second.second))
					{
						return iter->second.first.get()->ExecuteOnUp();
					}
				}
			}
		}
	}
	

	return true;
}

bool InputManager::IsPressed(ControllerButton button, XBox360Controller* controller) const
{
	return controller->IsPressed(static_cast<unsigned int>(button));
}

bool InputManager::IsDownThisFrame(ControllerButton button, XBox360Controller* controller) const
{
	return controller->IsDown(static_cast<unsigned int>(button));
}

bool InputManager::IsUpThisFrame(ControllerButton button, XBox360Controller* controller) const
{
	return controller->IsUp(static_cast<unsigned int>(button));
}

void InputManager::AddController(XBox360Controller* controller)
{
	m_Controllers.push_back(controller);
}

void InputManager::RemoveControllerBinding(ControllerButton button, int controllerIndex)
{
	auto it = m_ControllerCommandsMap.find(button);
	if(it->second.second == controllerIndex)
		m_ControllerCommandsMap.erase(it);
}


