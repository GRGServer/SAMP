ShowDialog:REGISTER_BIRTHDATE(playerID)
{
	CreateDialog(playerID, "REGISTER_BIRTHDATE", DIALOG_STYLE_INPUT, LanguageString(playerID, 253), LanguageString(playerID, 254), LanguageString(playerID, 177), LanguageString(playerID, 171));
}

DialogResponse:REGISTER_BIRTHDATE(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new day;
		new month;
		new year;
		if (sscanf(inputText, "p.ddd", day, month, year))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 40);
			ShowDialog:REGISTER_BIRTHDATE(playerID);
		}
		else
		{
			if (day > 0 && day <= 31 && month > 0 && month <=12 && year > 1900 && year < 2100)
			{
				SetPVarStr:playerID[BIRTHDATE][STRINGLENGTH_DATETIME]("%d-%02d-%02d", year, month, day);
				ShowDialog:REGISTER_LOCATION(playerID);
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 41);
				ShowDialog:REGISTER_BIRTHDATE(playerID);
			}
		}
	}
	else
	{
		ShowDialog:REGISTER_GENDER(playerID);
	}
}