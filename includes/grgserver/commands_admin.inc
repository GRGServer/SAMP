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

PCMD:jetpack[ADMIN](playerid, params[], "Bekomme ein Jetpack")
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	SendClientMessage(playerid, COLOR_INFO, "Viel Spaß mit deinem neuen JetPack!");
	return COMMAND_OK;
}

PCMD:money[ADMIN](playerid, params[], "Gebe dir Geld")
{
	new string[256];
	new Float:money;
	if (!sscanf(params, "f", money))
	{
		GivePlayerMoneyEx(playerid, money);
		Format:string("Du hast dir $%s gegeben", FormatMoney(money));
		SendClientMessage(playerid, COLOR_INFO, string);
		Format:string("Neuer Kontostand: %s", FormatMoney(GetPlayerMoneyEx(playerid)));
		SendClientMessage(playerid, COLOR_INFO, string);
		return COMMAND_OK;
	}
	else
	{
		CmdUsageMsg(playerid, "money", "Wert");
		return COMMAND_USAGE;
	}
}

PCMD:reloadplayer[ADMIN](playerid, params[], "Lade die Daten eines Spielers erneut von der Datenbank")
{
	new targetPlayerID;
	if (!sscanf(params, "u", targetPlayerID))
	{
		CmdUsageMsg(playerid, "reloadplayer", "PlayerID/Name");
		return COMMAND_USAGE;
	}
	if (targetPlayerID == INVALID_PLAYER_ID)
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
	LoadPlayer(targetPlayerID);
	return COMMAND_OK;
}