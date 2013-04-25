PCMD:resetcam[SERVERADMIN](playerID, params[], StringID:192("Set camera behind your player"))
{
	SetCameraBehindPlayer(playerID);
	return COMMAND_OK;
}