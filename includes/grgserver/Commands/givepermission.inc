PCMD:givepermission[SERVERADMIN](playerID, params[], 103)
{
	new targetPlayerID;
	new permissionString[256];
	if (sscanf(params, "us", targetPlayerID, permissionString))
	{
		CmdUsageMsg(playerID, "givepermission", "PlayerID/Name", "Admin|Mapper|Moderator|Navi|NPCAdmin|ServerAdmin|Teleport");
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
				if (permissionID == -1)
				{
					SendClientMessageEx(playerID, COLOR_ERROR, 381, permission);
				}
				else
				{
					if (permissions[targetPlayerID][enum_permission:permissionID] == newState)
					{
						if (newState)
						{
							SendClientMessageEx(playerID, COLOR_ERROR, 70, targetPlayerID, permission);
						}
						else
						{
							SendClientMessageEx(playerID, COLOR_ERROR, 71, targetPlayerID, permission);
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
						SendClientMessageEx(targetPlayerID, COLOR_INFO, 72, permission, playerID);
						SendClientMessageEx(playerID, COLOR_INFO, 73, permission, targetPlayerID);
						printf("%s got permission %s by %s", GetPlayerNameEx(targetPlayerID), permission, GetPlayerNameEx(playerID));
					}
					else
					{
						SendClientMessageEx(targetPlayerID, COLOR_INFO, 74, playerID, permission);
						SendClientMessageEx(playerID, COLOR_INFO, 75, permission, targetPlayerID);
						printf("%s has revoked the permission %s of %s", GetPlayerNameEx(playerID), permission, GetPlayerNameEx(targetPlayerID));
					}
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