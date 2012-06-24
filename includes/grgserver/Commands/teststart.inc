CMD:teststart(playerID, params[], 0)
{
	PVar:playerID[INTUTORIAL] = true;
	SpawnPlayer(playerID);
	return COMMAND_OK;
}