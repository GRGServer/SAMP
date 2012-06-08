ShowDialog:BuyVehicle(playerID, Float:price)
{
	FormatNew:string[100](LanguageString(playerID, 244), FormatMoney(price));
	ShowMsgBox(playerID, "BuyVehicle", LanguageString(playerID, 245), string, MSGBOXSTYLE_YESNO);
}

DialogResponse:BuyVehicle(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new vehicleID = GetPlayerVehicleID(playerID);
		if (!vehicleID)
		{
			return false;
		}
		if (!VehicleProperty:vehicleID[SAVEID])
		{
			return false;
		}
		MySQLQuery("SELECT * FROM `vehicles` WHERE `ID` = '%d'", VehicleProperty:vehicleID[SAVEID]);
		mysql_store_result();
		new Float:price = floatstr(GetMySQLField("price"));
		new sellerUserID = strval(GetMySQLField("OwnerSellerID"));
		mysql_free_result();
		if (price <= PVar:playerID[BANKMONEY])
		{
			GivePlayerMoneyEx(playerID, MONEY_CASH, -price);
			if (sellerUserID)
			{
				new sellerID = GetPlayerByUserID(sellerUserID);
				if (sellerID == INVALID_PLAYER_ID)
				{
					MySQLQuery("UPDATE `users` SET `BankMoney` = `BankMoney` + '%f' WHERE `ID` = '%d'", price, sellerUserID);
				}
				else
				{
					GivePlayerMoneyEx(sellerID, MONEY_CASH, price);
					SendClientMessageEx(sellerID, COLOR_INFO, 494, playerID);
				}
			}
			MySQLQuery("UPDATE `vehicles` SET `OwnerUserID` = '%d', `OwnerSellerID` = '0' WHERE `ID` = '%d'", PVar:playerID[USERID], VehicleProperty:vehicleID[SAVEID]);
			SendClientMessageEx(playerID, COLOR_INFO, 493);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 27, price, PVar:playerID[BANKMONEY]);
		}
	}
	return true;
}