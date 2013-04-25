ShowDialog:TeleportLocations(playerID)
{
	new locations[2048];
	mysql_query("SELECT `name` FROM `teleports`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		if (strlen(locations))
		{
			Format:locations("%s\n", locations);
		}
		Format:locations("%s%s", locations, GetMySQLField("name"));
	}
	mysql_free_result();
	CreateDialog(playerID, "TeleportLocations", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:246("Teleport")), locations, "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:TeleportLocations(playerID, response, listItem, inputText[])
{
	if (response)
	{
		MySQLQuery("SELECT * FROM `teleports` WHERE `name` = '%s'", MySQLEscapeString(inputText));
		mysql_store_result();
		if (mysql_num_rows())
		{
			Teleport(playerID, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ")), floatstr(GetMySQLField("angle")), strval(GetMySQLField("interior")), 0);
		}
		mysql_free_result();
	}
}