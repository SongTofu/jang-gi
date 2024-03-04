#include "MySQL.h"
#include "Define.h"
#include <iostream>

MySQL::MySQL()
{
	MYSQL conn;

	mysql_init(&conn);
	this->connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);

	if (this->connection == NULL)
	{
		fprintf(stderr, "Mysql connection error: %s\n", mysql_error(&conn));
		exit(1);
	}
	//query_stat = mysql_query(this->connection, "select 1");
	//if (query_stat != 0)
	//{
	//	fprintf(stderr, "Mysql querey error: %s\n", mysql_error(&conn));
	//	exit(1);
	//}

	//sql_result = mysql_store_result(this->connection);
	//while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	//	std::cout << sql_row[0] << std::endl;
	
}

MySQL::~MySQL()
{
	mysql_close(this->connection);
}

bool MySQL::Query(STRSAFE_LPCSTR query, ...) {
	char buf[1024] = "";
	va_list args;

	va_start(args, query);
	StringCbVPrintfA(buf, 1024, query, args);
	va_end(args);

	std::cout << buf << std::endl;
	return true;
}
