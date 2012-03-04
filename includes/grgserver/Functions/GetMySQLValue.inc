GetMySQLValue(table[], field[], checkColumn[], checkValue[], whereOperator[] = "=")
{
	MySQLQuery("SELECT `%s` FROM `%s` WHERE `%s` %s '%s'", MySQLEscapeString(field), MySQLEscapeString(table), MySQLEscapeString(checkColumn), whereOperator, MySQLEscapeString(checkValue));
	mysql_store_result();
	FormatNew:string[256]("%s", GetMySQLField(field));
	mysql_free_result();
	return string;
}