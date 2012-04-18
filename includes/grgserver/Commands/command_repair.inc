CMD:repair(playerid, params[], 296)
{
	if (PVar:playerid[JOBID] == JOB_ADAC)
	{
		new targetPlayerID;
		new Float:price;
		new vehicleID = GetPlayerVehicleID(playerid);
		new targetvehicleID = GetPlayerVehicleID(targetPlayerID);
		if (sscanf(params, "uf", targetPlayerID,price))
		{
			CmdUsageMsg(playerid, "repair", "Playername/ID", "Prise");
			return COMMAND_USAGE;
		}
		SetVehicleHealth(vehicleID, 1000.00);
		SetVehicleHealth(targetvehicleID, 1000.00);
		GivePlayerMoneyEx(targetPlayerID, MONEY_CASH, -price);
		GivePlayerMoneyEx(playerid, MONEY_CASH, price);
		return COMMAND_OK;
	}
	return COMMAND_PERMISSION_DENIED;
}