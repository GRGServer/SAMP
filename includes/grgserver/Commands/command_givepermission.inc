PCMD:givepermission[SERVERADMIN](playerid, params[], 103)
{
	new targetPlayerID;
	new permissionString[256];
	if (sscanf(params, "us", targetPlayerID, permissionString))
	{
		CmdUsageMsg(playerid, "givepermission", "Spielername", "Recht(Admin|Mapper|Moderator|NPCAdmin|ServerAdmin|Teleport)");
		return COMMAND_USAGE;
	}
	if (IsPlayerConnected(targetPlayerID))
	{
		new permissionsArray[30][30];
		new permission[30];
		explode(permissionString, permissionsArray, ',', sizeof(permissionsArray));
		for (new permissionIndex = 0; permissionIndex < sizeof(permissionsArray); permissionIndex++)
		{
			permission = permissionsArray[permissionIndex];
			if (strcmp(permission, "UserID", true))
			{
				new newState = true;
				if (permission[0] == '-')
				{
					strdel(permission, 0, 1);
					newState = false;
				}
				new permissionID = GetPermissionByName(permission);
				if (permissions[targetPlayerID][enum_permission:permissionID] == newState)
				{
					if (newState)
					{
						SendClientMessageEx(playerid, COLOR_ERROR, 70, targetPlayerID, permission);
					}
					else
					{
						SendClientMessageEx(playerid, COLOR_ERROR, 71, targetPlayerID, permission);
					}
					return COMMAND_ERROR;
				}
				MySQLQuery("SELECT `UserID` FROM `permissions` WHERE `UserID` = '%d'", PVar:targetPlayerID[USERID]);
				mysql_store_result();
				new rows = mysql_num_rows();
				mysql_free_result();
				if (rows)
				{
					MySQLQuery("UPDATE `permissions` SET `%s` = '%d' WHERE `UserID` = '%d'", MySQLEscapeString(permission), newState, PVar:targetPlayerID[USERID]);
				}
				else
				{
					MySQLQuery("INSERT INTO `permissions` (`UserID`, `%s`) VALUES('%d', '%d')", MySQLEscapeString(permission), PVar:targetPlayerID[USERID], newState);
				}
				permissions[targetPlayerID][enum_permission:permissionID] = newState;
				if (newState)
				{
					SendClientMessageEx(targetPlayerID, COLOR_INFO, 72, permission, playerid);
					SendClientMessageEx(playerid, COLOR_INFO, 73, permission, targetPlayerID);
					printf("%s got permission %s by %s", GetPlayerNameEx(targetPlayerID), permission, GetPlayerNameEx(playerid));
				}
				else
				{
					SendClientMessageEx(targetPlayerID, COLOR_INFO, 74, playerid, permission);
					SendClientMessageEx(playerid, COLOR_INFO, 75, permission, targetPlayerID);
					printf("%s has revoked the permission %s of %s", GetPlayerNameEx(playerid), permission, GetPlayerNameEx(targetPlayerID));
				}
			}
		}
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}