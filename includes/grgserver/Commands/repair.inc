CMD:repair(playerID, params[], StringID:296(""))
{
	if (PVar:playerID[JOBID] == JOB_ADAC)
	{
		new targetPlayerID;
		new Float:price;
		if (sscanf(params, "uf", targetPlayerID, price))
		{
			CmdUsageMsg(playerID, "repair", "Playername/ID", LanguageString(playerID, StringID:298("")));
			return COMMAND_USAGE;
		}
		if (PVar:targetPlayerID[MONEY] >= price)
		{
			if (IsPlayerInAnyVehicle(targetPlayerID))
			{
				PVar:targetPlayerID[REPAIR_EXECUTOR] = playerID;
				PVar:targetPlayerID[REPAIR_PRICE] = price;
				ShowDialog:Repair(targetPlayerID);
				SendClientMessageEx(playerID, COLOR_INFO, StringID:303(""));
				return COMMAND_OK;
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:300(""), targetPlayerID);
				return COMMAND_ERROR;
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:299(""), targetPlayerID);
			return COMMAND_ERROR;
		}
	}
	return COMMAND_PERMISSION_DENIED;
}