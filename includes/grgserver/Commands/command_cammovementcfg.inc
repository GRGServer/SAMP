PCMD:cammovementcfg[SERVERADMIN](playerID, params[], 194)
{
	if (!PVar:playerID[CAMERAMOVEMENT_EDITID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 190);
		return COMMAND_ERROR;
	}
	new type[20];
	new value[100];
	if (sscanf(params, "ss", type, value))
	{
		CmdUsageMsg(playerID, "cammovementcfg", "Type (Time, WaitStart, WaitEnd)", "Value");
		return COMMAND_USAGE;
	}
	if (!strcmp(type, "Time", true))// Time in ms to use from start position to end position
	{
		MySQLQuery("UPDATE `cameramovements` SET `Time` = '%d' WHERE `ID` = '%d'", strval(value), PVar:playerID[CAMERAMOVEMENT_EDITID]);
		SendClientMessageEx(playerID, COLOR_INFO, 193);
		return COMMAND_OK;
	}
	if (!strcmp(type, "WaitStart", true))// Time in ms to wait before moving the camera
	{
		MySQLQuery("UPDATE `cameramovements` SET `WaitStart` = '%d' WHERE `ID` = '%d'", strval(value), PVar:playerID[CAMERAMOVEMENT_EDITID]);
		SendClientMessageEx(playerID, COLOR_INFO, 193);
		return COMMAND_OK;
	}
	if (!strcmp(type, "WaitEnd", true))// Time in ms to wait after moving the camera before setting back behind the player
	{
		MySQLQuery("UPDATE `cameramovements` SET `WaitEnd` = '%d' WHERE `ID` = '%d'", strval(value), PVar:playerID[CAMERAMOVEMENT_EDITID]);
		SendClientMessageEx(playerID, COLOR_INFO, 193);
		return COMMAND_OK;
	}
	return COMMAND_ERROR;
}