public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (IsPlayerNPC(playerid))
	{
		return true;
	}
	new modelID = GetVehicleModel(vehicleid);
	if (modelID == 420)
	{
		PlayerLoop(npcPlayerID)
		{
			if (PVar:npcPlayerID[NPC_VEHICLEID] == vehicleid)
			{
				if (ispassenger)
				{
					SendNPCCommand(npcPlayerID, "start");
					return true;
				}
				else
				{
					RemovePlayerFromVehicle(playerid);
					return false;
				}
			}
		}
	}
	if (!ispassenger)
	{
		SetVehicleEngineState(vehicleid, false);
		if (!CheckVehiclePermission(playerid, vehicleid))
		{
			return false;
		}
	}
	return true;
}