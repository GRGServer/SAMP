PCMD:playcammovement[SERVERADMIN](playerID, params[], 189)
{
	if (!PVar:playerID[CAMERAMOVEMENT_EDITID])
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 190);
		return COMMAND_ERROR;
	}
	PlayCameraMovement(playerID, PVar:playerID[CAMERAMOVEMENT_EDITID]);
	SendClientMessageEx(playerID, COLOR_INFO, 191, PVar:playerID[CAMERAMOVEMENT_EDITID]);
	return COMMAND_OK;
}