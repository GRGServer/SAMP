ShowDialog:ADDNAVILOCATION_NEWTYPE(playerID)
{
	FormatNew:string[256](LanguageString(playerID, 382), FILE_LANGUAGESTRINGS);
	CreateDialog(playerID, "ADDNAVILOCATION_NEWTYPE", DIALOG_STYLE_INPUT, LanguageString(playerID, 378), string, "OK", LanguageString(playerID, 171));
}

DialogResponse:ADDNAVILOCATION_NEWTYPE(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (strlen(inputText))
		{
			MySQLQuery("INSERT INTO `navigationlocationtypes` (`Name`) VALUES('%s')", MySQLEscapeString(inputText));
			new typeID = mysql_insert_id();
			if (typeID)
			{
				new Float:posX;
				new Float:posY;
				new Float:posZ;
				GetPlayerPos(playerID, posX, posY, posZ);
				MySQLQuery("INSERT INTO `navigationlocations` (`Type`, `PosX`, `PosY`, `PosZ`) VALUES('%d', '%f', '%f', '%f')", typeID, posX, posY, posZ);
				SendClientMessageEx(playerID, COLOR_INFO, 383);
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 143);
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 379);
			ShowDialog:ADDNAVILOCATION_NEWTYPE(playerID);
		}
	}
	else
	{
		ShowDialog:ADDNAVILOCATION_TYPE(playerID);
	}
}