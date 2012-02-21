PCMD:goto[TELEPORT](playerid, params[])
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

PCMD:showinterior[TELEPORT](playerid, params[])
{
	if (GetPVarInt(playerid, "CurrentBuildingID"))
	{
		SendClientMessage(playerid, COLOR_ERROR, "Du bist aktuell in einem Gebäude! Bitte verlasse das Gebäude und versuche es erneut.");
		return COMMAND_ERROR;
	}
	else
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		GetPlayerPos(playerid, posX, posY, posZ);
		SetPVarFloat(playerid, "ShowInterior_OldPosX", posX);
		SetPVarFloat(playerid, "ShowInterior_OldPosY", posY);
		SetPVarFloat(playerid, "ShowInterior_OldPosZ", posZ);
		SetPVarInt(playerid, "ShowInterior_OldInterior", GetPlayerInterior(playerid));
		ShowInteriorDialog(playerid, INTERIORDIALOG_SHOWINTERIOR);
		return COMMAND_OK;
	}
}

PCMD:teleport[TELEPORT](playerid, params[])
{
	ShowDialog(playerid, DIALOG_TELEPORTLOCATIONS);
	return COMMAND_OK;
}