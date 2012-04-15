RemovePlayerCheckpoint(playerID)
{
	PVar:playerID[CURRENTCHECKPOINT] = 0;
	DisablePlayerCheckpoint(playerID);
}