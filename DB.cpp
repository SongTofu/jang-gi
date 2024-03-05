#include "DB.h"
#include "Define.h"
#include <iostream>

DB::DB()
{
	mysql_init(&conn);
	this->connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, "sakila", 3306, NULL, 0);

	if (this->connection == NULL)
	{
		fprintf(stderr, "[ERROR] Mysql connection %s\n", mysql_error(&conn));
		exit(1);
	}
	std::cout << "[Suceess] Connected with MySQL\n";
}

DB::~DB()
{
	mysql_close(this->connection);
}

DB& DB::operator>>(int& i)
{
	i = atoi(sql_row[index]);
	++index;
	return *this;
}

DB& DB::operator>>(short& sh)
{
	sh = atoi(sql_row[index]);
	++index;
	return *this;
}

DB& DB::operator>>(char& c)
{
	c = *(sql_row[index]);
	index++;
	return *this;
}

DB& DB::operator>>(std::string& str)
{
	str = sql_row[index];
	++index;
	return *this;
}

bool DB::Query(STRSAFE_LPCSTR query, ...) {
	char buf[1024] = "";
	va_list args;

	va_start(args, query);
	StringCbVPrintfA(buf, 1024, query, args);
	va_end(args);

	mysql_query(this->connection, buf);
	sql_result = mysql_store_result(this->connection);
	
	if (sql_result == NULL)
		return false;
	return true;
}

bool DB::Fetch()
{
	sql_row = mysql_fetch_row(sql_result);

	if (sql_row == NULL)
		return false;

	index = 0;
	return true;
}

