#include "IOCPServer.h"
#include "UserManager.h"

IOCPServer::IOCPServer() {}

IOCPServer::~IOCPServer()
{
	WSACleanup();
}

bool IOCPServer::Init(const UINT32 maxIOWorkerThreadCount_)
{
	WSADATA wsaData;

	int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (0 != nRet)
	{
		printf("[Error] WSAStartup()함수 실패 : %d\n", WSAGetLastError());
		return false;
	}

	//연결지향형 TCP , Overlapped I/O 소켓을 생성
	listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);

	if (INVALID_SOCKET == listenSocket)
	{
		printf("[Error] socket()함수 실패 : %d\n", WSAGetLastError());
		return false;
	}

	maxIOWorkerThreadCount = maxIOWorkerThreadCount_;

	printf("[Suceess] Socket Init\n");
	return true;
}

bool IOCPServer::BindandListen(int bindPort_)
{
	SOCKADDR_IN		stServerAddr;
	stServerAddr.sin_family = AF_INET;
	stServerAddr.sin_port = htons(bindPort_);
	stServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int nRet = bind(listenSocket, (SOCKADDR*)&stServerAddr, sizeof(SOCKADDR_IN));
	if (nRet != 0)
	{
		printf("[Error] bind()함수 실패 : %d\n", WSAGetLastError());
		return false;
	}

	nRet = listen(listenSocket, 7);
	if (nRet != 0)
	{
		printf("[Error] listen()함수 실패 : %d\n", WSAGetLastError());
		return false;
	}

	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, maxIOWorkerThreadCount);
	if (IOCPHandle == NULL)
	{
		printf("[Error] CreateIoCompletionPort()함수 실패 : %d\n", WSAGetLastError());
		return false;
	}

	//auto t_IOCPHandle = CreateIoCompletionPort((HANDLE)listenSocket, IOCPHandle, 0, 0);
	//if (nullptr == t_IOCPHandle)
	//{
	//	printf("[Error]  비동기 io bind 실패 : %d \n", WSAGetLastError());
	//	return false;
	//}

	printf("[Suceess] Server BindandListen\n");
	return true;
}


void IOCPServer::Run()
{
	accepterThread = std::thread([this]() { AcceptThread(); });
	for (int i = 0; i < MAX_WORKERTHREAD; i++)
	{
		IOWorkerThreads.emplace_back([this]() { CreateThread(); });
	}
}

void IOCPServer::AcceptThread()
{
	while (isRunning)
	{
		SOCKADDR_IN	sockAddr;
		int addrLen = sizeof(sockAddr);
		
		SOCKET sock = accept(listenSocket, (SOCKADDR*)&sockAddr, &addrLen);
		if (sock == INVALID_SOCKET)
		{
			printf("ERROR :: accept() 함수 실패 : %d\n", WSAGetLastError());
			continue;
		}

		User* user = UserManager::GetInstance()->CreateUser(sock);

		if (user == NULL)
		{
			closesocket(sock);
			continue;
		}
		
		HANDLE handle = CreateIoCompletionPort(reinterpret_cast<HANDLE>(user->GetSocket()), IOCPHandle, reinterpret_cast<ULONG_PTR>(user), 0);
		
		if (handle == NULL)
		{
			printf("ERROR :: CreateIoCompletionPort() 함수 실패\n");
			closesocket(sock);
			delete user;
			continue;
		}

		stOverlappedEx* overlapped = new stOverlappedEx();
		overlapped->wsaBuf.buf = user->GetBuf();
		overlapped->wsaBuf.len = user->GetRemainSize();
		overlapped->eOperation = IOOperation::RECV;

		DWORD dwFlag = 0;
		DWORD dwRecvNumBytes = 0;
		int ret = WSARecv(sock, &overlapped->wsaBuf, 1, &dwRecvNumBytes, &dwFlag, reinterpret_cast<LPWSAOVERLAPPED>(overlapped), NULL);

		if (ret == SOCKET_ERROR && (WSAGetLastError() != ERROR_IO_PENDING))
		{
			printf("ERORR :: WSARecv() 함수\n");
		}
	}

}

void IOCPServer::CreateThread()
{
	while (isRunning)
	{
		DWORD	numberOfBytes = 0;
		User* user = NULL;
		stOverlappedEx* overlapped;
		bool success = GetQueuedCompletionStatus(IOCPHandle, &numberOfBytes, reinterpret_cast<PULONG_PTR>(&user), reinterpret_cast<LPOVERLAPPED*>(&overlapped), INFINITE); //cpp 형변환
		
		if (success == false && GetLastError() == 258) {
			continue;
		}
		else if (success == false)
		{
			printf("ERROR :: GetQueuedCompletionStatus() 실패  %d\n", GetLastError());
			continue;
		}
	
		if (overlapped->eOperation == IOOperation::SEND)
		{
			this->Send();
		}

		else if (overlapped->eOperation == IOOperation::RECV && numberOfBytes != 0)
		{
			this->Receive(user, overlapped, numberOfBytes);
		}

		else if (overlapped->eOperation == IOOperation::RECV && numberOfBytes == 0)
		{
			this->Disconnect(user);
		}

	}
}

//void IOCPServer::CloseSocket(User* user)
//{
//	if (user == NULL)
//		return;
//
//	SOCKET sock = user->GetSocket();
//	struct linger stLinger = { 0, 0 };
//
//	shutdown(sock, SD_BOTH);
//
//	setsockopt(sock, SOL_SOCKET, SO_LINGER, (char*)&stLinger, sizeof(stLinger));
//
//	closesocket(sock);
//
//	user->SetSocket(INVALID_SOCKET);
//
//}

void IOCPServer::End()
{
	isRunning = false;
	closesocket(listenSocket);
	if (accepterThread.joinable())
	{
		accepterThread.join();
	}

	CloseHandle(IOCPHandle);
	for(auto& th :IOWorkerThreads)
	{
		if (th.joinable())
		{
			th.join();
		}
	}
}
