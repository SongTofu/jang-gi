#pragma once

#pragma comment(lib, "ws2_32")
//#pragma comment(lib, "mswsock.lib")

//#include "ClientInfo.h"
#include "User.h"
//#include <Ws2tcpip.h>
//#include <mswsock.h>
#include <thread>
#include <vector>

const UINT32 MAX_SOCK_RECVBUF = 256;	// 소켓 버퍼의 크기
const UINT32 MAX_SOCK_SENDBUF = 4096;	// 소켓 버퍼의 크기
const UINT64 RE_USE_SESSION_WAIT_TIMESEC = 3;
const UINT32 MAX_WORKERTHREAD = 4; 

enum class IOOperation
{
	ACCEPT,
	RECV,
	SEND
};

struct stOverlappedEx
{
	WSAOVERLAPPED wsaOverlapped;		//Overlapped I/O구조체
	WSABUF		wsaBuf;				//Overlapped I/O작업 버퍼
	IOOperation eOperation;			//작업 동작 종류
};

class IOCPServer
{
public:
	IOCPServer(void);
	virtual ~IOCPServer(void);

	bool Init(const UINT32 maxIOWorkerThreadCount_);
	bool BindandListen(int bindPort_);
	void Run();
	void AcceptThread();
	void	CreateThread();
	//void CloseSocket(User* user);
	void End();

	virtual void Connect() {};
	virtual void Disconnect(User* user) = 0;
	virtual void Receive(User* user, stOverlappedEx* overlapped, DWORD size) = 0;
	virtual void Send() = 0;
	// vsend 완료
	
private:
	SOCKET	listenSocket = INVALID_SOCKET;
	UINT32	maxIOWorkerThreadCount = 0;
	HANDLE	IOCPHandle = INVALID_HANDLE_VALUE;
	std::thread accepterThread;
	std::vector<std::thread> IOWorkerThreads;

	bool isRunning = true;

};

