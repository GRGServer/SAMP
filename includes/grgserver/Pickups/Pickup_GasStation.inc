PickupEvent:GASSTATION(playerID, pickupID)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (vehicleID)
	{
		new modelID = GetVehicleModel(vehicleID);
		if (modelID >= 400 && modelID <= 611)
		{
			new Float:maximum = floatsub(vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL], vehicles[vehicleID][VEHICLE_CURRENTFUEL]);
			if (maximum > 0)
			{
				ShowDialog(playerID, DIALOG_REFUEL, FormatMoney(maximum));
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 140);
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 146);
		}
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 146);
	}
}

PickupModelID:GASSTATION(pickupID)
{
	return 1008;
}