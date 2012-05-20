ShowGPSCheckpoint(playerID, id)
{
	new nextNodeID;
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	new Float:nextPosX;
	new Float:nextPosY;
	new Float:nextPosZ;
	if (id >= PVar:playerID[GPS_NODESCOUNT])
	{
		PVar:playerID[GPS_ENABLED] = false;
		return false;
	}
	PVar:playerID[GPS_ID] = id;
	GetNodePos(PVar:playerID[GPS_NODES][id], posX, posY, posZ);
	if (GetPlayerDistanceFromPoint(playerID, posX, posY, posZ) < 30 && id < PVar:playerID[GPS_NODESCOUNT] - 1)
	{
		return ShowGPSCheckpoint(playerID, id + 1);
	}
	for (nextNodeID = id + 1; nextNodeID < PVar:playerID[GPS_NODESCOUNT]; nextNodeID++)
	{
		GetNodePos(PVar:playerID[GPS_NODES][nextNodeID], nextPosX, nextPosY, nextPosZ);
		if (GetDistanceBetweenPoints(posX, posY, posZ, nextPosX, nextPosY, nextPosZ) >= 30)
		{
			break;
		}
	}
	SetPlayerRaceCheckpointEx(playerID, CHECKPOINT_NAVIGPS, Float:posX, Float:posY, Float:posZ, Float:nextPosX, Float:nextPosY, Float:nextPosZ, 5);
	return true;
}