ShowDialog:SelectInterior(playerID, dialogID, firstPage = true)
{
	new interiorList[2048];
	new firstItem;
	new lastItem;

	if (firstPage)
	{
		firstItem = 1;// The first (0) item is the world which is not a real interior
		lastItem = sizeof(interiors) / 2 - 1;
	}
	else
	{
		firstItem = sizeof(interiors) / 2;
		lastItem = sizeof(interiors) - 1;
	}

	for (new interiorID = firstItem; interiorID <= lastItem; interiorID++)
	{
		if (strlen(interiorList))
		{
			Format:interiorList("%s\n", interiorList);
		}
		Format:interiorList("%s%s", interiorList, interiors[interiorID][INTERIOR_NAME]);
	}

	if (firstPage)
	{
		Format:interiorList("%s\n%s", interiorList, LanguageString(playerID, "NEXT"));
	}
	else
	{
		Format:interiorList("%s\n%s", interiorList, LanguageString(playerID, "BACK"));
	}

	FormatNew:string[30]("%s", LanguageString(playerID, "247"));
	PVar:playerID[SELECTINTERIOR_ID] = dialogID;
	CreateDialog(playerID, "SelectInterior", DIALOG_STYLE_LIST, string, interiorList, "OK", LanguageString(playerID, "165"));
}

DialogResponse:SelectInterior(playerID, response, listItem, inputText[])
{
	if (!response)
	{
		OnInteriorDialogSelect(playerID,  PVar:playerID[SELECTINTERIOR_ID], 0);
		return true;
	}
	if (IsStr(inputText, LanguageString(playerID, "BACK")))
	{
		ShowDialog:SelectInterior(playerID,  PVar:playerID[SELECTINTERIOR_ID], true);
		return true;
	}
	if (IsStr(inputText, LanguageString(playerID, "NEXT")))
	{
		ShowDialog:SelectInterior(playerID,  PVar:playerID[SELECTINTERIOR_ID], false);
		return true;
	}

	Foreach(interiorID, interiors)
	{
		if (!strcmp(interiors[interiorID][INTERIOR_NAME], inputText))
		{
			OnInteriorDialogSelect(playerID,  PVar:playerID[SELECTINTERIOR_ID], interiorID);
			return true;
		}
	}

	return false;
}