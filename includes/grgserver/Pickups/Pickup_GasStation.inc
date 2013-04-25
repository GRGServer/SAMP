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
				new Float:maximum = floatsub(vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL], VehicleProperty:vehicleID[CURRENTFUEL]);
				if (maximum > 0)
				{
					PVar:playerID[REFUEL_MAXIMUM] = maximum;
					ShowDialog:Refuel(playerID);
				}
				else
				{
					SendClientMessageEx(playerID, COLOR_ERROR, StringID:140("The tank is already full!"));
				}
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:146("You are not in a vehicle!"));
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:146("You are not in a vehicle!"));
		}
		return true;
	}
	return false;
}

PickupModelID:GASSTATION(pickupID)
{
	return 1008;
}