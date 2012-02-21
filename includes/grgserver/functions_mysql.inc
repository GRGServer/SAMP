FetchMySQLRow()
{
	new Line[1024];
	return mysql_fetch_row(Line);
}

GetMySQLField(field[])
{
	new value[256];
	mysql_fetch_field(field, value);
	return value;
}

GetMySQLValue(table[], field[], checkColumn[], checkValue[], whereOperator[] = "=")
{
	new query[256];
	new string[256];
	format(query, sizeof(query), "SELECT `%s` FROM `%s` WHERE `%s` %s '%s'", MySQLEscapeString(field), MySQLEscapeString(table), MySQLEscapeString(checkColumn), whereOperator, MySQLEscapeString(checkValue));
	mysql_query(query);
	mysql_store_result();
	format(string, sizeof(string), "%s", GetMySQLField(field));
	mysql_free_result();
	return string;
}

MySQLEscapeString(string[])
{
	new escapedString[256];
	mysql_real_escape_string(string, escapedString);
	return escapedString;
}

SetMySQLValue(table[], field[], value[], checkColumn[], checkValue[])
{
	new query[1024];
	format(query, sizeof(query), "UPDATE `%s` SET `%s` = '%s' WHERE `%s` = '%s'", MySQLEscapeString(table), MySQLEscapeString(field), MySQLEscapeString(value), MySQLEscapeString(checkColumn), MySQLEscapeString(checkValue));
	mysql_query(query);
}