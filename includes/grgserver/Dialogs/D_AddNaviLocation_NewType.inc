ShowDialog:AddNaviLocation_NewType(playerID)
{
	FormatNew:string[256](LanguageString(playerID, StringID:382("Enter the name for the new type.\n\nUse L:[LanguageStringID] (e.g. L:329) to use a language string defined in %s.")), FILE_LANGUAGESTRINGS);
	CreateDialog(playerID, "AddNaviLocation_NewType", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:378("Add new type")), string, "OK", LanguageString(playerID, StringID:171("Back")));
}

DialogResponse:AddNaviLocation_NewType(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (strlen(inputText))
		{
			MySQLQuery("INSERT INTO `navigationlocationtypes` (`name`) VALUES('%s')", MySQLEscapeString(inputText));
			new typeID = mysql_insert_id();
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
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:379("You have to enter the name!"));
			ShowDialog:AddNaviLocation_NewType(playerID);
		}
	}
	else
	{
		ShowDialog:AddNaviLocation_Type(playerID);
	}
}