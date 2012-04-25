PCMD:usecammovement[SERVERADMIN](playerID, params[], 183)
{
	new movementID;
	if (sscanf(params, "d", movementID))
	{
		CmdUsageMsg(playerID, "usecammovement", "MovementID");
		return COMMAND_USAGE;
	}
	if (!strval(GetMySQLValue("cameramovements", "ID", "ID", val2str(movementID))))
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 187);
		return COMMAND_ERROR;
	}
	PVar:playerID[CAMERAMOVEMENT_EDITID] = movementID;
	SendClientMessageEx(playerID, COLOR_INFO, 188, PVar:playerID[CAMERAMOVEMENT_EDITID]);
	return COMMAND_OK;
}