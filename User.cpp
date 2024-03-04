#include "User.h"

bool User::AddSize(WORD size)
{
	if (size > MAX_BUF_SIZE)
	{
		printf("ERROR :: buf overflow \n");
		return false;
	}
	this->size += size;
	//���߿� ����� 
	printf("size: %d :: %s\n", this->size, this->buf);
	return true;
}

void	User::SetSocket(SOCKET socket)
{
	this->socket = socket;
}

SOCKET	User::GetSocket()
{
	return this->socket;
}


char* User::GetBuf()
{
	return &this->buf[this->size];
}

WORD	User::GetRemainSize()
{
	return MAX_BUF_SIZE - this->size;
}