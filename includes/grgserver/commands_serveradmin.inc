PCMD:givepermission[SERVERADMIN](playerid, params[])
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
			format(permission, sizeof(permission), permissionsArray[permissionIndex]);
			if (strcmp(permission, "UserID", true))
			{
				new newState = true;
				if (permission[0] == '-')
				{
					strdel(permission, 0, 1);
					newState = false;
				}
				new query[256];
				new string[256];
				new permissionID = GetPermissionByName(permission);
				if (permissions[playerid][enum_permission:permissionID] == newState)
				{
					if (newState)
					{
						format(string, sizeof(string), "%s hat bereits das Recht %s", GetPlayerNameEx(targetPlayerID), permission);
					}
					else
					{
						format(string, sizeof(string), "%s hatte das Recht %s noch nicht ud kann daher nicht entfernt werden", GetPlayerNameEx(targetPlayerID), permission);
					}
					SendClientMessage(playerid, COLOR_ERROR, string);
					return COMMAND_ERROR;
				}
				format(query, sizeof(query), "SELECT `UserID` FROM `permissions` WHERE `UserID` = '%d'", GetPVarInt(targetPlayerID, "UserID"));
				mysql_query(query);
				mysql_store_result();
				if (mysql_num_rows())
				{
					format(query, sizeof(query), "UPDATE `permissions` SET `%s` = '%d' WHERE `UserID` = '%d'", MySQLEscapeString(permission), newState, GetPVarInt(targetPlayerID, "UserID"));
				}
				else
				{
					format(query, sizeof(query), "INSERT INTO `permissions` (`UserID`, `%s`) VALUES('%d', '%d')", MySQLEscapeString(permission), GetPVarInt(targetPlayerID, "UserID"), newState);
				}
				mysql_free_result();
				mysql_query(query);
				permissions[targetPlayerID][enum_permission:permissionID] = newState;
				if (newState)
				{
					format(string, sizeof(string), "Du hast das Recht %s von %s bekommen!", permission, GetPlayerNameEx(playerid));
					SendClientMessage(targetPlayerID, COLOR_INFO, string);
					format(string, sizeof(string), "Du hast das Recht %s an %s gegeben!", permission, GetPlayerNameEx(targetPlayerID));
					SendClientMessage(playerid, COLOR_INFO, string);
					printf("%s got permission %s by %s", GetPlayerNameEx(targetPlayerID), permission, GetPlayerNameEx(playerid));
				}
				else
				{
					format(string, sizeof(string), "%s hat dir das Recht %s weggenommen!", GetPlayerNameEx(playerid), permission);
					SendClientMessage(targetPlayerID, COLOR_INFO, string);
					format(string, sizeof(string), "Du hast das Recht %s von %s weggenommen!", permission, GetPlayerNameEx(targetPlayerID));
					SendClientMessage(playerid, COLOR_INFO, string);
					printf("%s has removed the permission %s of %s", GetPlayerNameEx(playerid), permission, GetPlayerNameEx(targetPlayerID));
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

PCMD:gmx[SERVERADMIN](playerid, params[])
{
	ShowDialog(playerid, DIALOG_RESTARTGAMEMODE);
	return COMMAND_OK;
}

PCMD:rc[SERVERADMIN](playerid, params[])
{
	printf("%s sent a RCON command: %s", GetPlayerNameEx(playerid), params);
	SendRconCommand(params);
	SendClientMessage(playerid, COLOR_INFO, "Der Befehl wurde ausgeführt");
	return COMMAND_OK;
}