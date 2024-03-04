#pragma once

#include "IOCPServer.h"
class GameServer : public IOCPServer
{
public:
	GameServer() = default;
	virtual ~GameServer() = default;

	virtual void Connect() override {};

	virtual void Disconnect(User* user) override;

	virtual void Receive(User* user, stOverlappedEx* overlapped, DWORD size) override;

	virtual void Send() override;
};

