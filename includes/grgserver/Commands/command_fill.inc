CMD:fill(playerid, params[], 297)
{
	if (PVar:playerid[JOBID] == JOB_ADAC)
	{
		new targetPlayerID;
		new Float:price;
		new vehicleID = GetPlayerVehicleID(playerid);
		if (sscanf(params, "uf", targetPlayerID,price))
		{
			CmdUsageMsg(playerid, "fill", "Playername/ID", "Prise");
			return COMMAND_USAGE;
		}
		Timer_RefuelVehicle(vehicleID, 100.00);
		GivePlayerMoneyEx(targetPlayerID, MONEY_CASH, -price);
		GivePlayerMoneyEx(playerid, MONEY_CASH, price);
		return COMMAND_OK;
	}
	return COMMAND_PERMISSION_DENIED;
}