PCMD:givepermission[SERVERADMIN](playerid, params[], "Rechte an einen Spieler geben")
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
			Format:permission(permissionsArray[permissionIndex]);
			if (strcmp(permission, "UserID", true))
			{
				new newState = true;
				if (permission[0] == '-')
				{
					strdel(permission, 0, 1);
					newState = false;
				}
				new string[256];
				new permissionID = GetPermissionByName(permission);
				if (permissions[targetPlayerID][enum_permission:permissionID] == newState)
				{
					if (newState)
					{
						Format:string("%s hat bereits das Recht %s", GetPlayerNameEx(targetPlayerID), permission);
					}
					else
					{
						Format:string("%s hatte das Recht %s noch nicht und kann daher nicht entfernt werden", GetPlayerNameEx(targetPlayerID), permission);
					}
					SendClientMessage(playerid, COLOR_ERROR, string);
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
					Format:string("Du hast das Recht %s von %s bekommen!", permission, GetPlayerNameEx(playerid));
					SendClientMessage(targetPlayerID, COLOR_INFO, string);
					Format:string("Du hast das Recht %s an %s gegeben!", permission, GetPlayerNameEx(targetPlayerID));
					SendClientMessage(playerid, COLOR_INFO, string);
					printf("%s got permission %s by %s", GetPlayerNameEx(targetPlayerID), permission, GetPlayerNameEx(playerid));
				}
				else
				{
					Format:string("%s hat dir das Recht %s weggenommen!", GetPlayerNameEx(playerid), permission);
					SendClientMessage(targetPlayerID, COLOR_INFO, string);
					Format:string("Du hast das Recht %s von %s weggenommen!", permission, GetPlayerNameEx(targetPlayerID));
					SendClientMessage(playerid, COLOR_INFO, string);
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