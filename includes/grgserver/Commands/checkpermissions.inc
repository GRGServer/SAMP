PCMD:checkpermissions[ADMIN](playerid, params[], StringID:99("Show the permissions of yourself or another player"))
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
				strcat(string, GetPermissionName(permission));
			}
		}
		if (targetPlayerID == playerid)
		{
			SendClientMessageEx(playerid, COLOR_INFO, StringID:59("You have the following permissions: %s"), string);
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_INFO, StringID:60("%p has the following permissions: %s"), targetPlayerID, string);
		}
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}