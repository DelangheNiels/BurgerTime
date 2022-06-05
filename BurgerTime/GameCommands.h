#pragma once

#include "Command.h"

using namespace dae;

class QuitCommand final : public Command
{
public:
	QuitCommand(GameObject* gameObject);
	virtual ~QuitCommand() = default;
	QuitCommand(const QuitCommand& other) = default;
	QuitCommand(QuitCommand && other) = default;
	QuitCommand& operator=(const QuitCommand & other) = default;
	QuitCommand& operator=(QuitCommand && other) = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class MoveLeftCommand final : public Command
{
public:
	MoveLeftCommand(GameObject* gameObject);
	virtual ~MoveLeftCommand() = default;
	MoveLeftCommand(const MoveLeftCommand& other) = default;
	MoveLeftCommand(MoveLeftCommand && other) = default;
	MoveLeftCommand& operator=(const MoveLeftCommand & other) = default;
	MoveLeftCommand& operator=(MoveLeftCommand && other) = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class MoveRightCommand final : public Command
{
public:
	MoveRightCommand(GameObject* gameObject);
	virtual ~MoveRightCommand() = default;
	MoveRightCommand(const MoveRightCommand& other) = default;
	MoveRightCommand(MoveRightCommand && other) = default;
	MoveRightCommand& operator=(const MoveRightCommand & other) = default;
	MoveRightCommand& operator=(MoveRightCommand && other) = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class MoveUpCommand final : public Command
{
public:
	MoveUpCommand(GameObject* gameObject);
	virtual ~MoveUpCommand() = default;
	MoveUpCommand(const MoveUpCommand& other) = default;
	MoveUpCommand(MoveUpCommand && other) = default;
	MoveUpCommand& operator=(const MoveUpCommand & other) = default;
	MoveUpCommand& operator=(MoveUpCommand && other) = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class MoveDownCommand final : public Command
{
public:
	MoveDownCommand(GameObject* gameObject);
	virtual ~MoveDownCommand() = default;
	MoveDownCommand(const MoveDownCommand& other) = default;
	MoveDownCommand(MoveDownCommand && other) = default;
	MoveDownCommand& operator=(const MoveDownCommand & other) = default;
	MoveDownCommand& operator=(MoveDownCommand && other) = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class SelectSinglePlayerCommand final : public Command
{
public:
	SelectSinglePlayerCommand(GameObject* gameObject);
	virtual ~SelectSinglePlayerCommand() = default;
	SelectSinglePlayerCommand(const SelectSinglePlayerCommand& other) = default;
	SelectSinglePlayerCommand(SelectSinglePlayerCommand && other) = default;
	SelectSinglePlayerCommand& operator=(const SelectSinglePlayerCommand & other) = default;
	SelectSinglePlayerCommand& operator=(SelectSinglePlayerCommand && other) = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

class SelectMultiPlayerCommand final : public Command
{
public:
	SelectMultiPlayerCommand(GameObject* gameObject);
	virtual ~SelectMultiPlayerCommand() = default;
	SelectMultiPlayerCommand(const SelectMultiPlayerCommand& other) = default;
	SelectMultiPlayerCommand(SelectMultiPlayerCommand && other) = default;
	SelectMultiPlayerCommand& operator=(const SelectMultiPlayerCommand & other) = default;
	SelectMultiPlayerCommand& operator=(SelectMultiPlayerCommand && other) = default;
	bool ExecuteOnHold() override;
	bool ExecuteOnUp() override;
	bool ExecuteOnDown() override;
};

