SetPlayerRaceCheckpointEx(playerID, checkpointID, Float:posX, Float:posY, Float:posZ, Float:nextPosX, Float:nextPosY, Float:nextPosZ, Float:size)
{
	new type;
	if (nextPosX == 0 && nextPosY == 0 && nextPosZ == 0)
	{
		type = 1;
	}
	else
	{
		type = 0;
	}
	SetPlayerRaceCheckpoint(playerID, type, posX, posY, posZ, nextPosX, nextPosY, nextPosZ, size);
	PVar:playerID[CURRENTRACECHECKPOINT] = checkpointID;
}