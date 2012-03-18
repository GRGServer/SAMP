LanguageString(playerID, stringID)
{
	new string[256];
	MySQLQuery("SELECT * FROM `languagestrings` WHERE `ID` = '%d'", stringID);
	mysql_store_result();
	if (mysql_num_rows())
	{
		if (!strcmp(PVar:playerID[LANGUAGE], "de", true))
		{
			mysql_fetch_field("German", string);
		}
		else
		{
			mysql_fetch_field("English", string);
		}
	}
	else
	{
		printf("Language string not found! (ID: %d)", stringID);
	}
	mysql_free_result();
	return string;
}