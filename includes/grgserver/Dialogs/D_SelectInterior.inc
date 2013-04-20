ShowDialog:SelectInterior(playerID, dialogID, startID)
{
	new interiors[2048];
	new page;
	if (startID)
	{
		page = 2;
	}
	else
	{
		page = 1;
	}
	MySQLQuery("SELECT `name` FROM `interiors` ORDER BY `name` ASC LIMIT %d,75", startID);
	mysql_store_result();
	while (FetchMySQLRow())
	{
		if (strlen(interiors))
		{
			Format:interiors("%s\n", interiors);
		}
		Format:interiors("%s%s", interiors, GetMySQLField("name"));
	}
	mysql_free_result();
	switch (page)
	{
		case 1:
		{
			Format:interiors("%s\n%s", interiors, LanguageString(playerID, "177"));
		}
		case 2:
		{
			Format:interiors("%s\n%s", interiors, LanguageString(playerID, "177"));
		}
	}
	FormatNew:string[30]("%s (%s %d)", LanguageString(playerID, "247"), LanguageString(playerID, "248"), page);
	PVar:playerID[SELECTINTERIOR_ID] = dialogID;
	CreateDialog(playerID, "SelectInterior", DIALOG_STYLE_LIST, string, interiors, "OK", LanguageString(playerID, "165"));
}

DialogResponse:SelectInterior(playerID, response, listItem, inputText[])
{
	if (!response)
	{
		OnInteriorDialogSelect(playerID,  PVar:playerID[SELECTINTERIOR_ID], 0);
		return true;
	}
	if (IsStr(inputText, LanguageString(playerID, "171")))
	{
		ShowDialog:SelectInterior(playerID,  PVar:playerID[SELECTINTERIOR_ID], 0);
		return true;
	}
	if (IsStr(inputText, LanguageString(playerID, "177")))
	{
		ShowDialog:SelectInterior(playerID,  PVar:playerID[SELECTINTERIOR_ID], 75);
		return true;
	}
	new interiorID = strval(GetMySQLValue("interiors", "id", "name", inputText));
	OnInteriorDialogSelect(playerID,  PVar:playerID[SELECTINTERIOR_ID], interiorID);
	return true;
}