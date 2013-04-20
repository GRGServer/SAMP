GetNavigationLocationTypeByName(playerID, name[])
{
	new typeID;
	MySQLQuery("SELECT `id` FROM `navigationlocationtypes` WHERE `name` = '%s'", MySQLEscapeString(name));
	mysql_store_result();
	if (mysql_num_rows())
	{
		typeID = strval(GetMySQLField("id"));
	}
	mysql_free_result();
	if (!typeID)
	{
		MySQLQuery("SELECT `id`, `name` FROM `navigationlocationtypes` WHERE `name` LIKE 'L:%%'");
		mysql_store_result();
		while (FetchMySQLRow())
		{
			new checkCharacter;
			new languageStringName[100];
			sscanf(GetMySQLField("name"), "p:cs", checkCharacter, languageStringName);
			if (IsStr(name, LanguageString(playerID, languageStringName)))
			{
				typeID = strval(GetMySQLField("id"));
				break;
			}
		}
		mysql_free_result();
	}
	return typeID;
}