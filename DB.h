#pragma once

#include "Singleton.h"
#include <mysql.h>
#include <strsafe.h>

class DB : public Singleton<DB> //DB ½Ì±ÛÅæ?
{
public:
	~DB();

	DB& operator>>(int& i);
	DB& operator>>(short& sh);
	DB& operator>>(char& c);
	DB& operator>>(std::string& str);

	bool Query(STRSAFE_LPCSTR query, ...);
	bool Fetch();
	friend Singleton;

protected:
	DB();

private:
	MYSQL* connection = 0;
	MYSQL_RES* sql_result = 0;
	MYSQL_ROW sql_row = 0;
	MYSQL conn;
	WORD	index = 0;
};

