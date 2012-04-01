PCMD:resetcam[SERVERADMIN](playerID, params[], 192)
{
	SetCameraBehindPlayer(playerID);
	return COMMAND_OK;
}