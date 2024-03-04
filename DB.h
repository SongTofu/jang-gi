#pragma once

#include "Singleton.h"
#include <mysql.h>
#include <strsafe.h>
//ΩÃ±€≈Ê ∆–≈œ
class DB : public Singleton<DB>
{
public:
	DB();
	~DB();
	bool Query(STRSAFE_LPCSTR query, ...);
private:
	MYSQL* connection = 0;
	MYSQL_RES* sql_result = 0;
	MYSQL_ROW sql_row = 0;
};

