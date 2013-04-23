CMD:killme(playerID, params[], StringID:623(""))
{
	SetPlayerHealth(playerID, 0.0);
	return COMMAND_OK;
}