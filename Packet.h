#pragma once

#include <windows.h>

enum class  PACKET_ID : UINT16
{
	SYS_USER_SIGNUP = 11,	
	SYS_USER_CONNECT = 12,
	SYS_USER_DISCONNECT = 13,
	SYS_END = 30,

	//DB
	DB_END = 199,

	//Client
	LOGIN_REQUEST = 201,
	LOGIN_RESPONSE = 202,
};