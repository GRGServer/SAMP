ShowDialog:Register_Birthdate(playerID)
{
	CreateDialog(playerID, "Register_Birthdate", DIALOG_STYLE_INPUT, LanguageString(playerID, 253), LanguageString(playerID, 254), LanguageString(playerID, 177), LanguageString(playerID, 171));
}

DialogResponse:Register_Birthdate(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new day;
		new month;
		new year;
		if (sscanf(inputText, "p.ddd", day, month, year))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 40);
			ShowDialog:Register_Birthdate(playerID);
		}
		else
		{
			if (day > 0 && day <= 31 && month > 0 && month <=12 && year > 1900 && year < 2100)
			{
				SetPVarStr:playerID[BIRTHDATE][STRINGLENGTH_DATETIME]("%d-%02d-%02d", year, month, day);
				ShowDialog:Register_Location(playerID);
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 41);
				ShowDialog:Register_Birthdate(playerID);
			}
		}
	}
	else
	{
		ShowDialog:Register_Gender(playerID);
	}
}