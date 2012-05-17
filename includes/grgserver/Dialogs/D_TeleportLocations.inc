ShowDialog:TeleportLocations(playerID)
{
	new locations[2048];
	mysql_query("SELECT * FROM `teleports`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		if (strlen(locations))
		{
			Format:locations("%s\n", locations);
		}
		Format:locations("%s%s", locations, GetMySQLField("Name"));
	}
	mysql_free_result();
	CreateDialog(playerID, "TeleportLocations", DIALOG_STYLE_LIST, LanguageString(playerID, 246), locations, "OK", LanguageString(playerID, 165));
}

DialogResponse:TeleportLocations(playerID, response, listItem, inputText[])
{
	if (response)
	{
		MySQLQuery("SELECT * FROM `teleports` WHERE `Name` = '%s'", MySQLEscapeString(inputText));
		mysql_store_result();
		if (mysql_num_rows())
		{
			Teleport(playerID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), floatstr(GetMySQLField("Angle")), strval(GetMySQLField("Interior")), 0);
		}
		mysql_free_result();
	}
}