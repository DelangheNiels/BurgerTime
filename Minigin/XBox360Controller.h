#pragma once
#include "Command.h"
#include <memory>

	class XBox360Controller final
	{

	public:
		void Update();

		bool IsDown(unsigned int button) const;
		bool IsUp(unsigned int button) const;
		bool IsPressed(unsigned int button) const;

		explicit XBox360Controller(int controllerIndex);
		~XBox360Controller();

	private:
		class XBox360ControllerImpl;
		XBox360ControllerImpl* pImpl{};
	};


