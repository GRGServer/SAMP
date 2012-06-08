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
		new saveID = VehicleProperty:vehicleID[SAVEID];
		new Float:price = floatstr(GetMySQLValue("vehicles", "Price", "ID", val2str(saveID)));
		MySQLQuery("SELECT `ID` FROM `vehicles` WHERE `ID` = '%d' AND `OwnerSellerID`", VehicleProperty:vehicleID[SAVEID]);
		mysql_store_result();
		new sellerID = mysql_num_rows();
		mysql_free_result();
		if(sellerID)
		{
			if (price <= PVar:playerID[BANKMONEY])
			{
				GivePlayerMoneyEx(playerID, MONEY_CASH, -price);
				GivePlayerMoneyEx(sellerID, MONEY_CASH, price);
				SetMySQLValue("vehicles", "OwnerUserID", val2str(PVar:playerID[USERID]), "ID", val2str(saveID));
				MySQLQuery("UPDATE `vehicles` SET `OwnerSellerID` = '0' WHERE `ID` = '%d'", PVar:playerID[USERID], saveID);
				SendClientMessageEx(playerID, COLOR_INFO, 493);
				SendClientMessageEx(playerID, COLOR_INFO, 494);
				VehicleProperty:vehicleID[ALLOWDESTROY] = true;
				VehicleProperty:vehicleID[ALLOWSAVE] = true;
				SavePlayer(playerID);
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 27, price, PVar:playerID[BANKMONEY]);
			}
		}
		else 
		{
			if (price <= PVar:playerID[BANKMONEY])
			{
				GivePlayerMoneyEx(playerID, MONEY_CASH, -price);
				SetMySQLValue("vehicles", "OwnerUserID", val2str(PVar:playerID[USERID]), "ID", val2str(saveID));
				VehicleProperty:vehicleID[ALLOWDESTROY] = true;
				VehicleProperty:vehicleID[ALLOWSAVE] = true;
				SavePlayer(playerID);
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 27, price, PVar:playerID[BANKMONEY]);
			}
		}
	}
}