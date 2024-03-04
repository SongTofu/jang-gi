#pragma once

#include "Singleton.h"
#include <mysql.h>
#include <strsafe.h>
//ΩÃ±€≈Ê ∆–≈œ
class MySQL : public Singleton<MySQL>
{
public:
	MySQL();
	~MySQL();
	bool Query(STRSAFE_LPCSTR query, ...);

private:
	MYSQL* connection;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
};

