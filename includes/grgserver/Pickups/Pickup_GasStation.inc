PickupEvent:GASSTATION(playerID, pickupID)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (vehicleID)
	{
		new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][VEHICLEMODEL_MAXFUEL], vehicles[vehicleID][VEHICLE_CURRENTFUEL]);
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

PickupModelID:GASSTATION(pickupID)
{
	return 1008;
}