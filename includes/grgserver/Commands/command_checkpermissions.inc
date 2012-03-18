PCMD:checkpermissions[ADMIN](playerid, params[], 99)
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
			SendClientMessageEx(playerid, COLOR_INFO, 59, string);
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_INFO, 60, targetPlayerID, string);
		}
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}