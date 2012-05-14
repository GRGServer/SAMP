CMD:refuel(playerID, params[], 297)
{
	if (PVar:playerID[JOBID] == JOB_ADAC)
	{
		new targetPlayerID;
		if (sscanf(params, "u", targetPlayerID))
		{
			CmdUsageMsg(playerID, "refuel", "Playername/ID");
			return COMMAND_USAGE;
		}
		new vehicleID = GetPlayerVehicleID(targetPlayerID);
		if (vehicleID)
		{
			new modelID = GetVehicleModel(vehicleID);
			if (modelID >= 400 && modelID <= 611)
			{
				ShowDialog:REFUEL(targetPlayerID);
				return COMMAND_OK;
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 300, targetPlayerID);
				return COMMAND_ERROR;
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 300, targetPlayerID);
			return COMMAND_ERROR;
		}
	}
	return COMMAND_PERMISSION_DENIED;
}