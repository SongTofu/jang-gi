
#include "GameServer.h"
#include "DB.h"


const UINT16 SERVER_PORT = 11021;
//const UINT16 MAX_CLIENT = 100; 
const UINT32 MAX_IO_WORKER_THREAD = 4;

int main(void) {
	
	GameServer server;

	server.Init(MAX_IO_WORKER_THREAD);

	server.BindandListen(SERVER_PORT);

	server.Run();

	// 쿼리 쓰는 법 좀 알기~

	//DB::GetInstance()->Query("select film_id, title, description from film");
	//while (DB::GetInstance()->Fetch()) {
	//	int film_id = 0;
	//	std::string title, description;

	//	*DB::GetInstance() >> film_id >> title >> description;
	//	std::cout << film_id << " " << title << " " << description << std::endl;
	//}
	
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
	server.End();
	return 0;

}