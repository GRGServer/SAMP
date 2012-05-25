/**
 * <summary>
 *	This callback gets called once the closest path node of a player changes.
 * </summary>
 *
 * <param name="playerid">
 *	The ID of the player for which the change event occured.
 * </param>
 *
 * <param name="old_NodeID">
 *	The previous node.
 * </param>
 *
 * <param name="new_NodeID">
 *	The new current node.
 * </param>
 *
 * <remarks>
 *	This callbacks checks if the GPS_ENABLED PVar is <b>true</b> and there is currently no path calculation in process for the player (GPS_ISCALCULATING).
 *	If that is the case, the position of the current shown checkpoint gets checked for a distance of over 50 units.
 *	If also that is the case, a message gets sent to the player and the new path gets calculated.
 * </remarks>
 */

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