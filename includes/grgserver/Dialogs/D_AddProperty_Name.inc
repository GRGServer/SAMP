ShowDialog:AddProperty_Name(playerID)
{
	CreateDialog(playerID, "AddProperty_Name", DIALOG_STYLE_INPUT, LanguageString(playerID, 168), LanguageString(playerID, 169), LanguageString(playerID, 170), LanguageString(playerID, 171));
}

DialogResponse:AddProperty_Name(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new pickupID;
		GetPlayerPos(playerID, posX, posY, posZ);
		pickupID = AddPickup(-1, PVar:playerID[ADDPROPERTY_TYPE], posX, posY, posZ, true);
		if (pickupID > 0)
		{
			MySQLQuery("INSERT INTO `properties` (`PickupID`, `InteriorID`, `Name`, `Price`) VALUES ('%d', '%d', '%s', '%f')", pickupID, PVar:playerID[ADDPROPERTY_INTERIORID], MySQLEscapeString(inputText), PVar:playerID[ADDPROPERTY_PRICE]);
			SendClientMessageEx(playerID, COLOR_INFO, 10, inputText, PVar:playerID[ADDPROPERTY_PRICE], mysql_insert_id());
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 6);
		}
	}
	else
	{
		ShowInteriorDialog(playerID, INTERIORDIALOG_ADDPROPERTY);
	}
}