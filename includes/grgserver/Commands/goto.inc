PCMD:goto[TELEPORT](playerid, params[], 106)
{
	new targetPlayerID;
	if (sscanf(params, "u", targetPlayerID))
	{
		CmdUsageMsg(playerid, "goto", "PlayerID/Name");
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		new Float:angle;
		GetPlayerPos(targetPlayerID, posX, posY, posZ);
		GetPlayerFacingAngle(targetPlayerID, angle);
		if (TeleportTo(playerid, posX, posY, posZ, angle, GetPlayerInterior(targetPlayerID), GetPlayerVirtualWorld(targetPlayerID)))
		{
			return COMMAND_TELEPORTED;
		}
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
	return COMMAND_ERROR;
}