ShowGPSCheckpoint(playerID, id)
{
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:nextPosX;
	new Float:nextPosY;
	new Float:nextPosZ;
	if (id >= PVar:playerID[GPS_NODESCOUNT])
	{
		return false;
	}
	PVar:playerID[GPS_ID] = id;
	GetNodePos(PVar:playerID[GPS_NODES][id], posX, posY, posZ);
	if (GetPlayerDistanceFromPoint(playerID, posX, posY, posZ) < 30 && id < PVar:playerID[GPS_NODESCOUNT] - 1)// TODO: Goal checkpoint appears twice?
	{
		return ShowGPSCheckpoint(playerID, id + 1);
	}
	for (new nextNode = id + 1; nextNode < PVar:playerID[GPS_NODESCOUNT] - 1; nextNode++)
	{
		GetNodePos(PVar:playerID[GPS_NODES][nextNode], nextPosX, nextPosY, nextPosZ);
		if (GetPlayerDistanceFromPoint(playerID, nextPosX, nextPosY, nextPosZ) >= 30)// TODO: Fix arrow direction (Should be set to the real next target)
		{
			break;
		}
	}
	SetPlayerRaceCheckpointEx(playerID, CHECKPOINT_NAVIGPS, Float:posX, Float:posY, Float:posZ, Float:nextPosX, Float:nextPosY, Float:nextPosZ, 5);
	return true;
}