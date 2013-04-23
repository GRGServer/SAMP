PCMD:resetcam[SERVERADMIN](playerID, params[], StringID:192(""))
{
	SetCameraBehindPlayer(playerID);
	return COMMAND_OK;
}