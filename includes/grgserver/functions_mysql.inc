FetchMySQLRow()
{
	new Line[1024];
	return mysql_fetch_row(Line);
}

GetMySQLField(field[])
{
	new value[1024];
	mysql_fetch_field(field, value);
	return value;
}

GetMySQLValue(table[], field[], checkColumn[], checkValue[], whereOperator[] = "=")
{
	printf("[GetMySQLValue] %s, %s, %s, %s, %s", table, field, checkColumn, checkValue, whereOperator);
	Format:sqlQuery("SELECT `%s` FROM `%s` WHERE `%s` %s '%s'", MySQLEscapeString(field), MySQLEscapeString(table), MySQLEscapeString(checkColumn), whereOperator, MySQLEscapeString(checkValue));
	mysql_query(sqlQuery);
	print("[GetMySQLValue] Query sent");
	mysql_store_result();
	print("[GetMySQLValue] Result stored");
	FormatNew:string[512]("%s", GetMySQLField(field));
	print("[GetMySQLValue] Result fetched");
	printf("[GetMySQLValue] Result: %s", string);
	mysql_free_result();
	print("[GetMySQLValue] Result freed");
	return string;
}

MySQLEscapeString(string[])
{
	new escapedString[512];
	mysql_real_escape_string(string, escapedString);
	return escapedString;
}

SetMySQLValue(table[], field[], value[], checkColumn[], checkValue[])
{
	MySQLQuery("UPDATE `%s` SET `%s` = '%s' WHERE `%s` = '%s'", MySQLEscapeString(table), MySQLEscapeString(field), MySQLEscapeString(value), MySQLEscapeString(checkColumn), MySQLEscapeString(checkValue));
}