
#include "GameServer.h"
#include "DB.h"


const UINT16 SERVER_PORT = 11021;
//const UINT16 MAX_CLIENT = 3; // 임시
const UINT32 MAX_IO_WORKER_THREAD = 4; //생각해봤나요????

void HelloTread2(int input)
{
	std::cout << input << std::endl;
}

int main(void) {
	
	//std::cout << "ClientInfo : " << mysql_get_client_info() << std::endl;
	GameServer server;

	server.Init(MAX_IO_WORKER_THREAD);

	server.BindandListen(SERVER_PORT);

	server.Run();

	//DB::GetInstance()->Query("%d %d %d\n", 1, 2, 3);
	printf("quit 시 종료\n");
	while (true)
	{
		std::string inputCmd;
		std::getline(std::cin, inputCmd);

		if (inputCmd == "quit")
		{
			break;
		}
	}
	
	//server.End()
	return 0;

}