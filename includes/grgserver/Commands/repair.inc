CMD:repair(playerID, params[], StringID:296("Repair vehicle"))
{
	if (PVar:playerID[JOBID] == JOB_ADAC)
	{
		new targetPlayerID;
		new Float:price;
		if (sscanf(params, "uf", targetPlayerID, price))
		{
			CmdUsageMsg(playerID, "repair", "Playername/ID", LanguageString(playerID, StringID:298("Price")));
			return COMMAND_USAGE;
		}
		if (PVar:targetPlayerID[MONEY] >= price)
		{
			if (IsPlayerInAnyVehicle(targetPlayerID))
			{
				PVar:targetPlayerID[REPAIR_EXECUTOR] = playerID;
				PVar:targetPlayerID[REPAIR_PRICE] = price;
				ShowDialog:Repair(targetPlayerID);
				SendClientMessageEx(playerID, COLOR_INFO, StringID:303("The request has been send to the player"));
				return COMMAND_OK;
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:300("%p is not in any vehicle"), targetPlayerID);
				return COMMAND_ERROR;
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:299("%p has not enought money!"), targetPlayerID);
			return COMMAND_ERROR;
		}
	}
	return COMMAND_PERMISSION_DENIED;
}