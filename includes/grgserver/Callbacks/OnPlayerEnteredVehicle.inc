OnPlayerEnteredVehicle(playerID, vehicleID, isPassenger)
{
	if (IsPlayerNPC(playerID))
	{
		return true;
	}
	new modelID = GetVehicleModel(vehicleID);
	if (modelID == 420)
	{
		PlayerLoop(npcPlayerID)
		{
			if (PVar:npcPlayerID[NPC_VEHICLEID] == vehicleID)
			{
				if (isPassenger)
				{
					SendNPCCommand(npcPlayerID, "start");
					return true;
				}
				else
				{
					RemovePlayerFromVehicle(playerID);
					return false;
				}
			}
		}
	}
	if (!isPassenger)
	{
		SetVehicleEngineState(vehicleID, false);
		if (!CheckVehiclePermission(playerID, vehicleID))
		{
			return false;
		}
	}
	return true;
}