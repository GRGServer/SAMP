ShowDialog:BuyVehicle(playerID, Float:price)
{
	FormatNew:string[100](LanguageString(playerID, 244), FormatMoney(price));
	ShowMsgBox(playerID, "BuyVehicle", LanguageString(playerID, 245), string, MSGBOXSTYLE_YESNO);
}

DialogResponse:BuyVehicle(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new saveID = vehicles[GetPlayerVehicleID(playerID)][VEHICLE_SAVEID];
		new Float:price = floatstr(GetMySQLValue("vehicles", "Price", "ID", val2str(saveID)));
		if (price <= PVar:playerID[BANKMONEY])
		{
			GivePlayerMoneyEx(playerID, MONEY_CASH, -price);
			SetMySQLValue("vehicles", "OwnerUserID", val2str(PVar:playerID[USERID]), "ID", val2str(saveID));
			SavePlayer(playerID);
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 27, price, PVar:playerID[BANKMONEY]);
			RemovePlayerFromVehicle(playerID);
		}
	}
	else
	{
		RemovePlayerFromVehicle(playerID);
	}
}