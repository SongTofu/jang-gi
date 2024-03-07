#pragma once

#include "Singleton.h"
#include "User.h"

#include <vector>

class UserManager : public Singleton<UserManager>
{
public:
	User* CreateUser(SOCKET sock);
	bool DeleteUser(SOCKET sock);

	~UserManager() {};

	friend Singleton;
protected:
	UserManager();

private:
	void Init();

	std::vector<User*> existUserList; // �����ִ� �ֵ� //List�� �ϱ�~~~~
	std::vector<User*> emptyUserList;
};

