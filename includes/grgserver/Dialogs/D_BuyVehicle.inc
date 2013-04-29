ShowDialog:BuyVehicle(playerID, Float:price)
{
	FormatNew:string[100](LanguageString(playerID, StringID:244("Do you want to buy this vehicle?\n\nPrice: $%s")), FormatMoney(price));
	CreateDialog(playerID, "BuyVehicle", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:245("Buy vehicle")), string, LanguageString(playerID, StringID:166("Yes")), LanguageString(playerID, StringID:167("No")));
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

		if (VehicleProperty:vehicleID[PRICE] <= PVar:playerID[BANK_MONEY])
		{
			GivePlayerMoneyEx(playerID, MONEY_BANK, -VehicleProperty:vehicleID[PRICE]);
			if (VehicleProperty:vehicleID[SELLERUSERID])
			{
				new sellerID = GetPlayerByUserID(VehicleProperty:vehicleID[SELLERUSERID]);
				if (sellerID == INVALID_PLAYER_ID)
				{
					MySQLQuery("UPDATE `users` SET `money` = `money` + '%f' WHERE `id` = '%d'", VehicleProperty:vehicleID[PRICE], VehicleProperty:vehicleID[SELLERUSERID]);
				}
				else
				{
					GivePlayerMoneyEx(sellerID, MONEY_BANK, VehicleProperty:vehicleID[PRICE]);
					SendClientMessageEx(sellerID, COLOR_INFO, StringID:494("%p has bought your vehicle"), playerID);
				}
			}

			VehicleProperty:vehicleID[OWNERUSERID] = PVar:playerID[USERID];
			VehicleProperty:vehicleID[SELLERUSERID] = 0;
			VehicleProperty:vehicleID[COLOR1] = VehicleProperty:vehicleID[CURRENTCOLOR1];
			VehicleProperty:vehicleID[COLOR2] = VehicleProperty:vehicleID[CURRENTCOLOR2];

			SendClientMessageEx(playerID, COLOR_INFO, StringID:493("You have bought a vehicle"));
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:27("You need %m to buy this vehicle! But you only have %m at your bank account."), VehicleProperty:vehicleID[PRICE], PVar:playerID[BANK_MONEY]);
		}
	}
	return true;
}