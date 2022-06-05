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

		XBox360Controller(int controllerIndex);
		~XBox360Controller();
		XBox360Controller(const XBox360Controller& other) = default;
		XBox360Controller(XBox360Controller && other) = default;
		XBox360Controller& operator=(const XBox360Controller & other) = default;
		XBox360Controller& operator=(XBox360Controller && other) = default;

	private:
		class XBox360ControllerImpl;
		XBox360ControllerImpl* pImpl{};
	};


