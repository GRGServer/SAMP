Timer:RefuelVehicle(playerID, Float:totalAmount)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (vehicleID)
	{
		if (PVar:playerID[MONEY] >= PVar:playerID[CURRENTGASPRICE])
		{
			new modelID = GetVehicleModel(vehicleID);
			if (modelID >= 400 && modelID <= 611)
			{
				new Float:maximum = floatsub(vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL], VehicleProperty:vehicleID[CURRENTFUEL]);
				if (totalAmount > 0 && maximum > 0)
				{
					new Float:amount;
					if (maximum < 1)
					{
						amount = maximum;
					}
					else
					{
						amount = 1.0;
					}
					VehicleProperty:vehicleID[CURRENTFUEL] = floatadd(VehicleProperty:vehicleID[CURRENTFUEL], amount);
					GivePlayerMoneyEx(playerID, MONEY_CASH, -floatmul(PVar:playerID[CURRENTGASPRICE], amount));
					SetTimerEx("Timer_RefuelVehicle", GASSTATION_REFUELSPEED, false, "df", playerID, floatsub(totalAmount, amount));
					return true;
				}
				SendClientMessageEx(playerID, COLOR_INFO, 91);
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 146);
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 92);
		}
	}
	TogglePlayerControllable(playerID, true);
	return true;
}