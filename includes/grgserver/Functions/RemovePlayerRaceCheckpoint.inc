RemovePlayerRaceCheckpoint(playerID)
{
	PVar:playerID[CURRENTRACECHECKPOINT] = 0;
	DisablePlayerRaceCheckpoint(playerID);
}