CMD:gps(playerID, params[], 0)
{
	new nodeID = NearestPlayerNode(playerID);
	if (nodeID == -1)
	{
		SendClientMessage(playerID, COLOR_ERROR, "No node found!");
		return COMMAND_ERROR;
	}
	if (PVar:playerID[MAP_POSX] && PVar:playerID[MAP_POSY])
	{
		new targetNodeID = NearestNodeFromPoint(PVar:playerID[MAP_POSX], PVar:playerID[MAP_POSY], PVar:playerID[MAP_POSZ]);
		if (targetNodeID == -1)
		{
			SendClientMessage(playerID, COLOR_ERROR, "No target node found!");
			return COMMAND_ERROR;
		}
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		GetNodePos(nodeID, posX, posY, posZ);
		SetPlayerMapIcon(playerID, 0, posX, posY, posZ, 38, 0);
		FormatNew:string[100]("Closest start node: %d (%f x %f x %f)", nodeID, posX, posY, posZ);
		SendClientMessage(playerID, COLOR_INFO, string);
		GetNodePos(targetNodeID, posX, posY, posZ);
		SetPlayerMapIcon(playerID, 1, posX, posY, posZ, 42, 0);
		Format:string("Closest end node: %d (%f x %f x %f)", targetNodeID, posX, posY, posZ);
		SendClientMessage(playerID, COLOR_INFO, string);
		CalculatePath(nodeID, targetNodeID, playerID);
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 264);
	}
	return COMMAND_ERROR;
}