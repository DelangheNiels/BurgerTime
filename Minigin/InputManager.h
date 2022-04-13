#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <map>
#include "XBox360Controller.h"


	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		ButtonUp = 0x0001,
		ButtonDown = 0x0002,
		ButtonLeft = 0x0004,
		ButtonRight = 0x0008,
		ButtonStart = 0x0010,
		buttonBack = 0x0020,
		buttonLeftShoulder = 0x0100,
		buttonRightShoulder = 0x0200,
		buttonLeftThumb = 0x0040,
		buttonRightThumb = 0x0080
	};

	class InputManager final : public dae::Singleton<InputManager>
	{
	public:
		
		~InputManager();

		bool ProcessInput();
		bool IsPressed(ControllerButton button, XBox360Controller* controller) const;

		bool IsDownThisFrame(ControllerButton button, XBox360Controller* controller) const;
		bool IsUpThisFrame(ControllerButton button, XBox360Controller* controller) const;

		void AddController(XBox360Controller* controller);

		template<class MyCommand>
		void AddControllerCommandBinding(ControllerButton button, GameObject* gameObject, int controllerIndex)
		{
			if (std::is_base_of<Command, MyCommand>())
			{
				m_ControllerCommandsMap.insert(std::pair<ControllerButton, std::pair<std::unique_ptr<Command>,int>>
					(button, std::make_pair(std::make_unique<MyCommand>(gameObject), controllerIndex)));
			}
		}

		void RemoveControllerBinding(ControllerButton button, int controllerIndex);

	private:

		//using ControllerCommandMap = std::map<ControllerButton, std::unique_ptr<Command>>;
		using ControllerCommandMap = std::map<ControllerButton, std::pair<std::unique_ptr<Command>,int>>;
		ControllerCommandMap m_ControllerCommandsMap{};

		std::vector<XBox360Controller* >m_Controllers{};
		
		
	};



