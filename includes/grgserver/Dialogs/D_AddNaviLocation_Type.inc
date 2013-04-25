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
		new languageStringID;
		if (!sscanf(string, "p<:>cd", checkCharacter, languageStringID))
		{
			if (checkCharacter == 'L')
			{
				Format:string(LanguageString(playerID, languageStringID));
			}
		}
		AddLine(options, string);
	}
	mysql_free_result();
	AddLine(options, LanguageString(playerID, StringID:378("Add new type")));
	CreateDialog(playerID, "AddNaviLocation_Type", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:377("Select location type")), options, "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:AddNaviLocation_Type(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (IsStr(inputText, LanguageString(playerID, StringID:378("Add new type"))))
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
				SendClientMessageEx(playerID, COLOR_INFO, StringID:383("The location has been added"));
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:143("An error occurred while processing the command!"));
			}
		}
	}
}