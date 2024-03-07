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

	std::vector<User*> existUserList; // 들어와있는 애들 //List로 하긔~~~~
	std::vector<User*> emptyUserList;
};

