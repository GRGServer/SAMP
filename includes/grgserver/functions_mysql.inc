FetchMySQLRow()
{
	new Line[1024];
	print("Fetch MySQL row");
	return mysql_fetch_row(Line);
}

GetMySQLField(field[])
{
	new value[1024];
	printf("Get MySQL field: %s", field);
	mysql_fetch_field(field, value);
	printf("Field value: %s", value);
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
	FormatNew:string[1024]("%s", GetMySQLField(field));
	print("[GetMySQLValue] Result fetched");
	printf("[GetMySQLValue] Result: %s", string);
	mysql_free_result();
	print("[GetMySQLValue] Result freed");
	return string;
}

MySQLEscapeString(string[])
{
	new escapedString[256];
	printf("Escape: %s", string);
	mysql_real_escape_string(string, escapedString);
	printf("Escaped: %s", escapedString);
	return escapedString;
}

SetMySQLValue(table[], field[], value[], checkColumn[], checkValue[])
{
	MySQLQuery("UPDATE `%s` SET `%s` = '%s' WHERE `%s` = '%s'", MySQLEscapeString(table), MySQLEscapeString(field), MySQLEscapeString(value), MySQLEscapeString(checkColumn), MySQLEscapeString(checkValue));
}