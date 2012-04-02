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
		CmdUsageMsg(playerID, "cammovementcfg", "Type (CallOnEnd, CutType, ResetOnEnd, Time, WaitEnd, WaitStart)", "Value");
		return COMMAND_USAGE;
	}
	if (!strcmp(type, "CallOnEnd", true))// Call a function or play another camera movement (#<MovementID>)
	{
		MySQLQuery("UPDATE `cameramovements` SET `CallOnEnd` = '%s' WHERE `ID` = '%d'", MySQLEscapeString(value), PVar:playerID[CAMERAMOVEMENT_EDITID]);
		SendClientMessageEx(playerID, COLOR_INFO, 193);
		return COMMAND_OK;
	}
	if (!strcmp(type, "CutType", true))// Type to cut the camera movement
	{
		new cutType;
		if (!strcmp(value, "CUT", true))
		{
			cutType = CAMERA_CUT;
		}
		if (!strcmp(value, "MOVE", true))
		{
			cutType = CAMERA_MOVE;
		}
		if (cutType)
		{
			MySQLQuery("UPDATE `cameramovements` SET `CutType` = '%d' WHERE `ID` = '%d'", cutType, PVar:playerID[CAMERAMOVEMENT_EDITID]);
			SendClientMessageEx(playerID, COLOR_INFO, 193);
			return COMMAND_OK;
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 198);
			return COMMAND_ERROR;
		}
	}
	if (!strcmp(type, "ResetOnEnd", true))// Set the camera back behind the player after moving the camera or not
	{
		MySQLQuery("UPDATE `cameramovements` SET `ResetOnEnd` = '%d' WHERE `ID` = '%d'", strval(value), PVar:playerID[CAMERAMOVEMENT_EDITID]);
		SendClientMessageEx(playerID, COLOR_INFO, 193);
		return COMMAND_OK;
	}
	if (!strcmp(type, "Time", true))// Time in ms to use from start position to end position
	{
		MySQLQuery("UPDATE `cameramovements` SET `Time` = '%d' WHERE `ID` = '%d'", strval(value), PVar:playerID[CAMERAMOVEMENT_EDITID]);
		SendClientMessageEx(playerID, COLOR_INFO, 193);
		return COMMAND_OK;
	}
	if (!strcmp(type, "WaitEnd", true))// Time in ms to wait after moving the camera before doing additional steps (e.g. reser camera, call a function or play another camera movement)
	{
		MySQLQuery("UPDATE `cameramovements` SET `WaitEnd` = '%d' WHERE `ID` = '%d'", strval(value), PVar:playerID[CAMERAMOVEMENT_EDITID]);
		SendClientMessageEx(playerID, COLOR_INFO, 193);
		return COMMAND_OK;
	}
	if (!strcmp(type, "WaitStart", true))// Time in ms to wait before moving the camera
	{
		MySQLQuery("UPDATE `cameramovements` SET `WaitStart` = '%d' WHERE `ID` = '%d'", strval(value), PVar:playerID[CAMERAMOVEMENT_EDITID]);
		SendClientMessageEx(playerID, COLOR_INFO, 193);
		return COMMAND_OK;
	}
	return COMMAND_ERROR;
}