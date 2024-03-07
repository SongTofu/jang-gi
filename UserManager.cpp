#include "UserManager.h"
#include "Define.h"

UserManager::UserManager()
{
	Init();
}

void UserManager::Init()
{
	for (int i = 0; i < MAX_USER_CNT; ++i)
		emptyUserList.push_back(new User());
}

User* UserManager::CreateUser(SOCKET sock)
{
	for (int i = 0; i < existUserList.size(); ++i)
	{
		if (sock == existUserList[i]->GetSocket())
			return NULL;
	}

	User* user;

	if (emptyUserList.empty())
	{
		user = new User();
	}
	else 
	{
		user = emptyUserList.back();
		emptyUserList.pop_back();
	}

	user->SetSocket(sock);
	existUserList.push_back(user);

	return user;
}

bool UserManager::DeleteUser(SOCKET sock)
{
	if (existUserList.empty())
		return false;


	for (int i = 0; i < existUserList.size(); ++i)
	{
		if (sock == existUserList[i]->GetSocket())
		{
			User* user = existUserList[i];
			existUserList.erase(existUserList.begin() + i);
			user->Init();
			emptyUserList.push_back(user);
			return true;
		}
	}
	return false;
}