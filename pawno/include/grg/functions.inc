stock getMySQLField(field[])
{
	new value[256];
	mysql_fetch_field(field, value);
	return value;
}

stock mySQLEscapeString(string[])
{
	new escapedString[1024];
	mysql_real_escape_string(string, escapedString);
	return escapedString;
}