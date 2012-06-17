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
		GetPlayerPos(playerID, posX, posY, posZ);
		MySQLQuery("INSERT INTO `pickups` (`posX`, `posY`, `posZ`, `type`) VALUES('%f', '%f', '%f', '%s')", posX, posY, posZ, PVar:playerID[ADDPROPERTY_TYPE]);
		new pickupID = mysql_insert_id();
		if (pickupID)
		{
			if (AddPickup(pickupID, PVar:playerID[ADDPROPERTY_TYPE], posX, posY, posZ))
			{
				MySQLQuery("INSERT INTO `properties` (`pickupId`, `interiorId`, `name`, `price`) VALUES ('%d', '%d', '%s', '%f')", pickupID, PVar:playerID[ADDPROPERTY_INTERIORID], MySQLEscapeString(inputText), PVar:playerID[ADDPROPERTY_PRICE]);
				new propertyID = mysql_insert_id();
				if (IsStr(PVar:playerID[ADDPROPERTY_TYPE], "BANK"))
				{
					MySQLQuery("INSERT INTO `bankbranches` (`propertyId`, `bankId`) SELECT '%d', `id` FROM `banks` ORDER BY RAND() LIMIT 1", propertyID);
				}
				SendClientMessageEx(playerID, COLOR_INFO, 10, inputText, PVar:playerID[ADDPROPERTY_PRICE], propertyID);
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 6);
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 6);
		}
	}
	else
	{
		if (IsStr(PVar:playerID[ADDPROPERTY_TYPE], "BANK") || IsStr(PVar:playerID[ADDPROPERTY_TYPE], "HOTEL") || IsStr(PVar:playerID[ADDPROPERTY_TYPE], "PLACE"))
		{
			ShowDialog:AddProperty_Type(playerID);
		}
		else
		{
			ShowInteriorDialog(playerID, INTERIORDIALOG_ADDPROPERTY);
		}
	}
}