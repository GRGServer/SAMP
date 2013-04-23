ShowDialog:Repair(playerID)
{
	FormatNew:string[100](LanguageString(playerID, StringID:302("")), GetPlayerNameEx(PVar:playerID[REPAIR_EXECUTOR]), FormatMoney(PVar:playerID[REPAIR_PRICE]));
	CreateDialog(playerID, "Repair", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:301("")), string, LanguageString(playerID, StringID:166("")), LanguageString(playerID, StringID:167("")));
}

DialogResponse:Repair(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new vehicleID = GetPlayerVehicleID(playerID);
		if (vehicleID)
		{
			RepairVehicle(vehicleID);
			GivePlayerMoneyEx(playerID, MONEY_CASH, -PVar:playerID[REPAIR_PRICE]);
			GivePlayerMoneyEx(PVar:playerID[REPAIR_EXECUTOR], MONEY_CASH, PVar:playerID[REPAIR_PRICE]);
			SendClientMessageEx(playerID, COLOR_INFO, StringID:304(""));
			SendClientMessageEx(PVar:playerID[REPAIR_EXECUTOR], COLOR_INFO, StringID:305(""), GetPlayerNameEx(playerID), FormatMoney(PVar:playerID[REPAIR_PRICE]));
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:146(""));
		}
	}
	else
	{
		SendClientMessageEx(PVar:playerID[REPAIR_EXECUTOR], COLOR_ERROR, StringID:306(""), GetPlayerNameEx(playerID));
	}
	return true;
}