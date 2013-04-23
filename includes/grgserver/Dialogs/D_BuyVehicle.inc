ShowDialog:BuyVehicle(playerID, Float:price)
{
	FormatNew:string[100](LanguageString(playerID, StringID:244("")), FormatMoney(price));
	CreateDialog(playerID, "BuyVehicle", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:245("")), string, LanguageString(playerID, StringID:166("")), LanguageString(playerID, StringID:167("")));
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
		MySQLQuery("SELECT `id` FROM `vehicles` WHERE `id` = '%d'", VehicleProperty:vehicleID[SAVEID]);
		mysql_store_result();
		new isSavedVehicle = mysql_num_rows();
		mysql_free_result();
		new Float:bankMoney = GetBankMoney(playerID);
		if (VehicleProperty:vehicleID[PRICE] <= bankMoney)
		{
			GivePlayerMoneyEx(playerID, MONEY_BANK, -VehicleProperty:vehicleID[PRICE]);
			if (VehicleProperty:vehicleID[SELLERUSERID])
			{
				new sellerID = GetPlayerByUserID(VehicleProperty:vehicleID[SELLERUSERID]);
				if (sellerID == INVALID_PLAYER_ID)
				{
					MySQLQuery("SELECT `bankAccountId` FROM `users` WHERE `id` = '%d'", VehicleProperty:vehicleID[SELLERUSERID]);
					mysql_store_result();
					new bankAccountID = strval(GetMySQLField("bankAccountId"));
					mysql_free_result();
					if (bankAccountID)
					{
						MySQLQuery("UPDATE `bankaccounts` SET `money` = `money` + '%f' WHERE `id` = '%d'", VehicleProperty:vehicleID[PRICE], bankAccountID);
					}
				}
				else
				{
					GivePlayerMoneyEx(sellerID, MONEY_BANK, VehicleProperty:vehicleID[PRICE]);
					SendClientMessageEx(sellerID, COLOR_INFO, StringID:494(""), playerID);
				}
			}
			if (!isSavedVehicle)
			{
				MySQLQuery("INSERT INTO `vehicles` (`id`, `numberplate`) VALUES('%d', '%s')", VehicleProperty:vehicleID[SAVEID], CreateUniqueNumberplateText());
			}
			VehicleProperty:vehicleID[OWNERUSERID] = PVar:playerID[USERID];
			VehicleProperty:vehicleID[SELLERUSERID] = 0;
			VehicleProperty:vehicleID[COLOR1] = VehicleProperty:vehicleID[CURRENTCOLOR1];
			VehicleProperty:vehicleID[COLOR2] = VehicleProperty:vehicleID[CURRENTCOLOR2];
			SendClientMessageEx(playerID, COLOR_INFO, StringID:493(""));
			MySQLQuery("SELECT `vehicleBought` FROM `users` WHERE `id` = '%d'", PVar:playerID[USERID]);
			mysql_store_result();
			new vehicleBought = strval(GetMySQLField("vehicleBought"));
			mysql_free_result();
			if (!vehicleBought)
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:523(""));
				SendClientMessageEx(playerID, COLOR_INFO, StringID:524(""));
				SendClientMessageEx(playerID, COLOR_INFO, StringID:525(""));
				SendClientMessageEx(playerID, COLOR_INFO, StringID:526(""));
				SendClientMessageEx(playerID, COLOR_INFO, StringID:527(""));
				SendClientMessageEx(playerID, COLOR_INFO, StringID:528(""));
				MySQLQuery("UPDATE `users` SET `vehicleBought` = '1' WHERE `id` = '%d'", PVar:playerID[USERID]);
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:27(""), VehicleProperty:vehicleID[PRICE], bankMoney);
		}
	}
	return true;
}