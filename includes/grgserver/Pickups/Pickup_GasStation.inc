PickupEvent:GASSTATION(playerID, pickupID, eventType)
{
	if (eventType == PICKUPEVENT_KEYPRESS)
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
					PVar:playerID[REFUEL_MAXIMUM] = maximum;
					ShowDialog:REFUEL(playerID);
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
		return true;
	}
	return false;
}

PickupModelID:GASSTATION(pickupID)
{
	return 1008;
}