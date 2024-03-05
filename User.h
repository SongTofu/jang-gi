#pragma once

//#include <Windows.h>
#include <winsock2.h>
#include <iostream>

#define MAX_BUF_SIZE 8000

class User
{
public:
	User() = default;
	~User() = default;

	bool AddSize(WORD size);
	void SetSocket(SOCKET socket);

	SOCKET	GetSocket();
	char* GetBuf();
	WORD	GetRemainSize();

private:
	UINT32	index;
	char buf[MAX_BUF_SIZE] = {};
	WORD	size = 0;
	SOCKET	socket = NULL;

	std::string	userId;
};

