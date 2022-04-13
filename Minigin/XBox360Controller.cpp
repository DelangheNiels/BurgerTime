#pragma once
#include "MiniginPCH.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include "XBox360Controller.h"
#include <iostream>

class XBox360Controller::XBox360ControllerImpl
{
	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};

	WORD buttonPressedThisFrame;
	WORD buttonReleasedThisFrame;

	int _controllerIndex;

public:
	XBox360ControllerImpl(int controllerInedx)
		:_controllerIndex{ controllerInedx }
	{
		ZeroMemory(&previousState, sizeof(XINPUT_STATE));
		ZeroMemory(&previousState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		// todo: read the input
		CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(_controllerIndex, &currentState);

		auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
		buttonPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
		buttonReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);

	}

	bool IsDownThisFrame(unsigned int button) const
	{
		return buttonPressedThisFrame & button;
	}

	bool IsUpThisFrame(unsigned int button) const
	{
		return buttonReleasedThisFrame & button;
	}

	bool IsPressed(unsigned int button) const
	{
		return currentState.Gamepad.wButtons & button;
	}
};


void XBox360Controller::Update()
{
	pImpl->Update();
}

bool XBox360Controller::IsDown(unsigned int button) const
{
	return pImpl->IsDownThisFrame(button);
}

bool XBox360Controller::IsUp(unsigned int button) const
{
	return pImpl->IsUpThisFrame(button);
}

bool XBox360Controller::IsPressed(unsigned int button) const
{
	return pImpl->IsPressed(button);
}

XBox360Controller::XBox360Controller(int controllerIndex)
{
	pImpl = new XBox360ControllerImpl(controllerIndex);
}

XBox360Controller::~XBox360Controller()
{
	delete pImpl;
}