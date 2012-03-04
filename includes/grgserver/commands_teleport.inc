PCMD:goto[TELEPORT](playerid, params[], "Zu einen anderen Spieler teleportieren")
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

PCMD:showinterior[TELEPORT](playerid, params[], "In einen Interior teleportieren")
{
	if (GetPVar:playerid[CURRENTBUILDINGID])
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
		SetPVar:playerid[SHOWINTERIOR_OLDPOSX](posX);
		SetPVar:playerid[SHOWINTERIOR_OLDPOSY](posY);
		SetPVar:playerid[SHOWINTERIOR_OLDPOSZ](posZ);
		SetPVar:playerid[SHOWINTERIOR_OLDINTERIOR](GetPlayerInterior(playerid));
		ShowInteriorDialog(playerid, INTERIORDIALOG_SHOWINTERIOR);
		return COMMAND_OK;
	}
}

PCMD:teleport[TELEPORT](playerid, params[], "An einen vordefinierten Ort teleportieren")
{
	ShowDialog(playerid, DIALOG_TELEPORTLOCATIONS);
	return COMMAND_OK;
}