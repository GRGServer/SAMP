CMD:teststart(playerID, params[], 0)
{
	PVar:playerID[SPAWNAFTERREGISTER] = true;
	SpawnPlayer(playerID);
	return COMMAND_OK;
}