ShowDialog:Repair(playerID)
{
	FormatNew:string[100](LanguageString(playerID, StringID:302("%s wants to repair your vehicle for %s\n\nIs that OK?")), GetPlayerNameEx(PVar:playerID[REPAIR_EXECUTOR]), FormatMoney(PVar:playerID[REPAIR_PRICE]));
	CreateDialog(playerID, "Repair", DIALOG_STYLE_MSGBOX, LanguageString(playerID, StringID:296("Repair vehicle")), string, LanguageString(playerID, StringID:166("Yes")), LanguageString(playerID, StringID:167("No")));
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
			SendClientMessageEx(playerID, COLOR_INFO, StringID:304("Your vehicle has been repaired"));
			SendClientMessageEx(PVar:playerID[REPAIR_EXECUTOR], COLOR_INFO, StringID:305("%s has accepted your repair request. You get %s."), GetPlayerNameEx(playerID), FormatMoney(PVar:playerID[REPAIR_PRICE]));
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:146("You are not in a vehicle!"));
		}
	}
	else
	{
		SendClientMessageEx(PVar:playerID[REPAIR_EXECUTOR], COLOR_ERROR, StringID:306("%s has rejected your repair request."), GetPlayerNameEx(playerID));
	}
	return true;
}