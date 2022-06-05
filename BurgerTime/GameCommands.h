#pragma once

#include "Command.h"

using namespace dae;

class QuitCommand final : public Command
{
public:
	QuitCommand(GameObject* gameObject);
	virtual ~QuitCommand() = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class MoveLeftCommand final : public Command
{
public:
	MoveLeftCommand(GameObject* gameObject);
	virtual ~MoveLeftCommand() = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class MoveRightCommand final : public Command
{
public:
	MoveRightCommand(GameObject* gameObject);
	virtual ~MoveRightCommand() = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class MoveUpCommand final : public Command
{
public:
	MoveUpCommand(GameObject* gameObject);
	virtual ~MoveUpCommand() = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class MoveDownCommand final : public Command
{
public:
	MoveDownCommand(GameObject* gameObject);
	virtual ~MoveDownCommand() = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class SelectSinglePlayerCommand final : public Command
{
public:
	SelectSinglePlayerCommand(GameObject* gameObject);
	virtual ~SelectSinglePlayerCommand() = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class SelectMultiPlayerCommand final : public Command
{
public:
	SelectMultiPlayerCommand(GameObject* gameObject);
	virtual ~SelectMultiPlayerCommand() = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};


