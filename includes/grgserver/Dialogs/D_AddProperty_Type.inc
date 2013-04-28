ShowDialog:AddProperty_Type(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:173("Bank")));
	AddLine(options, LanguageString(playerID, StringID:174("Hotel")));
	AddLine(options, LanguageString(playerID, StringID:175("House")));
	AddLine(options, LanguageString(playerID, StringID:397("Place")));
	AddLine(options, LanguageString(playerID, StringID:176("Police")));
	AddLine(options, LanguageString(playerID, StringID:17("Shop")));
	CreateDialog(playerID, "AddProperty_Type", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:172("Select property type")), options, LanguageString(playerID, StringID:177("Next")), LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:AddProperty_Type(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new type[STRINGLENGTH_PROPERTYTYPE];
		if (IsStr(inputText, LanguageString(playerID, StringID:173("Bank"))))
		{
			type = "BANK";
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:174("Hotel"))))
		{
			type = "HOTEL";
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:175("House"))))
		{
			type = "HOUSE";
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:397("Place"))))
		{
			type = "PLACE";
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:176("Police"))))
		{
			type = "POLICE";
		}
		if (IsStr(inputText, LanguageString(playerID, StringID:17("Shop"))))
		{
			type = "SHOP";
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