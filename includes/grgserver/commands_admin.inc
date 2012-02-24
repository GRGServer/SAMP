PCMD:checkpermissions[ADMIN](playerid, params[])
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
					format(string, sizeof(string), "%s, ", string);
				}
				format(string, sizeof(string), "%s%s", string, GetPermissionName(permission));
			}
		}
		if (targetPlayerID == playerid)
		{
			format(string, sizeof(string), "Du hast die folgenden Rechte: %s", string);
		}
		else
		{
			format(string, sizeof(string), "%s hat die folgenden Rechte: %s", GetPlayerNameEx(targetPlayerID), string);
		}
		SendClientMessage(playerid, COLOR_INFO, string);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}

PCMD:jetpack[ADMIN](playerid, params[])
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	SendClientMessage(playerid, COLOR_INFO, "Viel Spaß mit deinem neuen JetPack!");
	return COMMAND_OK;
}

PCMD:money[ADMIN](playerid, params[])
{
	new string[256];
	new Float:money;
	if (!sscanf(params, "f", money))
	{
		GivePlayerMoneyEx(playerid, money);
		format(string, sizeof(string), "Du hast dir $%s gegeben", FormatMoney(money));
		SendClientMessage(playerid, COLOR_INFO, string);
		format(string, sizeof(string), "Neuer Kontostand: %s", FormatMoney(GetPlayerMoneyEx(playerid)));
		SendClientMessage(playerid, COLOR_INFO, string);
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "money", "Wert");
		return COMMAND_USAGE;
	}
}