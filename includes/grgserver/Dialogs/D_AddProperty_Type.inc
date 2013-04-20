ShowDialog:AddProperty_Type(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, "173"));
	AddLine(options, LanguageString(playerID, "174"));
	AddLine(options, LanguageString(playerID, "175"));
	AddLine(options, LanguageString(playerID, "397"));
	AddLine(options, LanguageString(playerID, "176"));
	CreateDialog(playerID, "AddProperty_Type", DIALOG_STYLE_LIST, LanguageString(playerID, "172"), options, LanguageString(playerID, "NEXT"), LanguageString(playerID, "165"));
}

DialogResponse:AddProperty_Type(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new type[STRINGLENGTH_PROPERTYTYPE];
		if (IsStr(inputText, LanguageString(playerID, "173")))
		{
			type = "BANK";
		}
		if (IsStr(inputText, LanguageString(playerID, "174")))
		{
			type = "HOTEL";
		}
		if (IsStr(inputText, LanguageString(playerID, "175")))
		{
			type = "HOUSE";
		}
		if (IsStr(inputText, LanguageString(playerID, "397")))
		{
			type = "PLACE";
		}
		if (IsStr(inputText, LanguageString(playerID, "176")))
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