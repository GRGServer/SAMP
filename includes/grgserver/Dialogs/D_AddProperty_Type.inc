ShowDialog:AddProperty_Type(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:173("")));
	AddLine(options, LanguageString(playerID, StringID:174("")));
	AddLine(options, LanguageString(playerID, StringID:175("")));
	AddLine(options, LanguageString(playerID, StringID:397("")));
	AddLine(options, LanguageString(playerID, StringID:176("")));
	CreateDialog(playerID, "AddProperty_Type", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:172("")), options, LanguageString(playerID, StringID:177("")), LanguageString(playerID, StringID:165("")));
}

DialogResponse:AddProperty_Type(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new type[STRINGLENGTH_PROPERTYTYPE];
		if (IsStr(inputText, LanguageString(playerID, StringID:173(""))))
		{
			type = "BANK";
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:174(""))))
		{
			type = "HOTEL";
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:175(""))))
		{
			type = "HOUSE";
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:397(""))))
		{
			type = "PLACE";
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:176(""))))
		{
			type = "POLICE";
		}
		SetPVarStr:playerID[ADDPROPERTY_TYPE][STRINGLENGTH_PROPERTYTYPE](type);
		if (IsStr(type, "BANK") || IsStr(type, "HOTEL") || IsStr(type, "PLACE"))
		{
			PVar:playerID[ADDPROPERTY_INTERIORID] = 0;
			ShowDialog:AddProperty_Name(playerID);
			return true;
		}
		ShowInteriorDialog(playerID, INTERIORDIALOG_ADDPROPERTY);
	}
	return true;
}