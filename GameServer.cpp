#include "GameServer.h"

void GameServer::Receive(User* user, stOverlappedEx* overlapped, DWORD size) {
	user->AddSize(size);
	
	overlapped->wsaBuf.buf = user->GetBuf();
	overlapped->wsaBuf.len = user->GetRemainSize();
	overlapped->eOperation = IOOperation::RECV;

	DWORD dwFlag = 0;
	DWORD dwRecvNumBytes = 0;
	
	WSARecv(user->GetSocket(), &overlapped->wsaBuf, 1, &dwRecvNumBytes, &dwFlag, reinterpret_cast<LPWSAOVERLAPPED>(overlapped), NULL);
}

void GameServer::Disconnect(User* user)
{
	//closesocket
	closesocket(user->GetSocket());

	//유저 비우기
	delete user;
}

void GameServer::Send()
{

}