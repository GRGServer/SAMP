PCMD:playcammovement[SERVERADMIN](playerID, params[], 189)
{
	new movementID;
	if (sscanf(params, "d", movementID))
	{
		if (!PVar:playerID[CAMERAMOVEMENT_EDITID])
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 190);
			return COMMAND_ERROR;
		}
		movementID = PVar:playerID[CAMERAMOVEMENT_EDITID];
	}
	else
	{
		if (!strval(GetMySQLValue("cameramovements", "ID", "ID", val2str(movementID))))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 187);
			return COMMAND_ERROR;
		}
	}
	PlayCameraMovement(playerID, movementID);
	SendClientMessageEx(playerID, COLOR_INFO, 191, movementID);
	return COMMAND_OK;
}