PCMD:checkpermissions[ADMIN](playerid, params[], "Rechte von dir oder einem anderen Spieler anzeigen")
{
	new targetPlayerID;
	new string[1024];
	if (sscanf(params, "u", targetPlayerID))
	{
		targetPlayerID = playerid;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		for (new permission = 0; permission < sizeof(permissions[]); permission++)
		{
			if (permissions[targetPlayerID][enum_permission:permission])
			{
				if (strlen(string))
				{
					Format:string("%s, ", string);
				}
				Format:string("%s%s", string, GetPermissionName(permission));
			}
		}
		if (targetPlayerID == playerid)
		{
			Format:string("Du hast die folgenden Rechte: %s", string);
		}
		else
		{
			Format:string("%s hat die folgenden Rechte: %s", GetPlayerNameEx(targetPlayerID), string);
		}
		SendClientMessage(playerid, COLOR_INFO, string);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}