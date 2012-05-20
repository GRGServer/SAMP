CalculateRoute(playerID, Float:posX, Float:posY, Float:posZ)
{
	new currentNodeID = NearestPlayerNode(playerID);
	if (currentNodeID == -1)
	{
		return false;
	}
	new targetNodeID = NearestNodeFromPoint(posX, posY, posZ);
	if (targetNodeID == -1)
	{
		return false;
	}
	PVar:playerID[GPS_ENABLED] = true;
	PVar:playerID[GPS_TARGETNODEID] = targetNodeID;
	PVar:playerID[GPS_ISCALCULATING] = true;
	CalculatePath(currentNodeID, targetNodeID, playerID);
	return true;
}