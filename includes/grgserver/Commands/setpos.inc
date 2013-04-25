PCMD:setpos[ADMIN](playerID, params[], StringID:463("Set the position and rotation for the current selected object to move to"))
{
	SetPlayerPos(playerID, 0,0,0);
	return COMMAND_OK;
}