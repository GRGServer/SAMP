CMD:killme(playerID, params[], 623)
{
	SetPlayerHealth(playerID, 0.0);
	return COMMAND_OK;
}