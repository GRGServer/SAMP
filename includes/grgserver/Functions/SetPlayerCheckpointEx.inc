SetPlayerCheckpointEx(playerID, checkpointID, Float:posX, Float:posY, Float:posZ, Float:size)
{
	SetPlayerCheckpoint(playerID, posX, posY, posZ, size);
	PVar:playerID[CURRENTCHECKPOINT] = checkpointID;
}