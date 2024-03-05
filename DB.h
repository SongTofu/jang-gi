#pragma once

#include "Singleton.h"
#include <mysql.h>
#include <strsafe.h>

class DB : public Singleton<DB>
{
public:
	DB();
	~DB();

	DB& operator>>(int& i);
	DB& operator>>(short& sh);
	DB& operator>>(char& c);
	DB& operator>>(std::string& str);

	bool Query(STRSAFE_LPCSTR query, ...);
	bool Fetch();

private:
	MYSQL* connection = 0;
	MYSQL_RES* sql_result = 0;
	MYSQL_ROW sql_row = 0;
	MYSQL conn;
	WORD	index;
};

