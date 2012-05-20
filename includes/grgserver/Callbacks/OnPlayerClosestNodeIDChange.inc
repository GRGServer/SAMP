public OnPlayerClosestNodeIDChange(playerid, old_NodeID, new_NodeID)
{
	if (PVar:playerid[GPS_ENABLED] && !PVar:playerid[GPS_ISCALCULATING])
	{
		new Float:currentCPPosX;
		new Float:currentCPPosY;
		new Float:currentCPPosZ;
		GetNodePos(PVar:playerid[GPS_NODES][PVar:playerid[GPS_ID]], currentCPPosX, currentCPPosY, currentCPPosZ);
		if (GetPlayerDistanceFromPoint(playerid, currentCPPosX, currentCPPosY, currentCPPosZ) > 50)
		{
			PVar:playerid[GPS_ISCALCULATING] = true;
			SendClientMessageEx(playerid, COLOR_INFO, 414);
			CalculatePath(new_NodeID, PVar:playerid[GPS_TARGETNODEID], playerid);
		}
	}
}