ShowDialog:AddNaviLocation_Type(playerID)
{
	new options[2048];
	MySQLQuery("SELECT * FROM `navigationlocationtypes`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new string[256];
		strcat(string, GetMySQLField("name"));
		new checkCharacter;
		new languageStringName[STRINGLENGTH_LANGUAGESTRINGNAME];
		if (!sscanf(string, "p<:>cs[" #STRINGLENGTH_LANGUAGESTRINGNAME "]", checkCharacter, languageStringName))
		{
			if (checkCharacter == 'L')
			{
				Format:string(LanguageString(playerID, languageStringName));
			}
		}
		AddLine(options, string);
	}
	mysql_free_result();
	AddLine(options, LanguageString(playerID, "378"));
	CreateDialog(playerID, "AddNaviLocation_Type", DIALOG_STYLE_LIST, LanguageString(playerID, "377"), options, "OK", LanguageString(playerID, "165"));
}

DialogResponse:AddNaviLocation_Type(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (IsStr(inputText, LanguageString(playerID, "378")))
		{
			ShowDialog:AddNaviLocation_NewType(playerID);
		}
		else
		{
			new typeID = GetNavigationLocationTypeByName(playerID, inputText);
			if (typeID)
			{
				new Float:posX;
				new Float:posY;
				new Float:posZ;
				GetPlayerPos(playerID, posX, posY, posZ);
				MySQLQuery("INSERT INTO `navigationlocations` (`type`, `posX`, `posY`, `posZ`) VALUES('%d', '%f', '%f', '%f')", typeID, posX, posY, posZ);
				SendClientMessageEx(playerID, COLOR_INFO, "383");
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, "143");
			}
		}
	}
}