CmdUsageMsg(playerID, command[], ...)
{
	new string[256];
	new value[256];
	new parameters;
	parameters = numargs();
	format(string, sizeof(string), "Verwendung: /%s", command);
	for (new index = 2; index < parameters; index++)
	{
		GetStringArg(index, value);
		format(string, sizeof(string), "%s %s", string, value);
	}
	SendClientMessage(playerID, COLOR_USAGE, string);
}

FormatPrice(Float:price)
{
	return FormatNumber(price, 2, '.', ',');
}

PlayRadioStation(playerID, id)
{
	if (id)
	{
		SetPVarInt(playerID, "RadioOn", true);
		SetPVarInt(playerID, "LastRadioStation", id);
		new name[256];
		format(name, sizeof(name), "%s", GetMySQLValue("radiostations", "Name", "ID", val2str(id)));
		PlayAudioStreamForPlayer(playerID, GetMySQLValue("radiostations", "URL", "ID", val2str(id)));
		TextDrawSetString(textDrawRadioStation[playerID], name);
		TextDrawShowForPlayer(playerID, textDrawRadioStation[playerID]);
		new string[256];
		format(string, sizeof(string), "Du hörst jetzt %s", name);
		SendClientMessage(playerID, COLOR_INFO, string);
	}
	else
	{
		SendClientMessage(playerID, COLOR_ERROR, "Ungültiger Radiosender!");
	}
}

RemoveNewLine(string[])
{
	new length = strlen(string);
	while (length-- && string[length] <= ' ')
	{
		string[length] = '\0';
	}
}

SendClientMessageToAdmins(permission, color, message[])
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerConnected(playerID) && permissions[playerID][enum_permission:permission])
		{
			SendClientMessage(playerID, color, message);
		}
	}
}

SendClientMessageToAllExcept(exceptPlayerID, color, message[])
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (playerID != exceptPlayerID && IsPlayerConnected(playerID))
		{
			SendClientMessage(playerID, color, message);
		}
	}
}

StopRadioStation(playerID)
{
	StopAudioStreamForPlayer(playerID);
	TextDrawHideForPlayer(playerID, textDrawRadioStation[playerID]);
}

UpdateGasPrice()
{
	gasPrice = float(150 + random(10)) / 100;
}

WriteChatToDatabase(playerID, text[])
{
	new query[512];
	format(query, sizeof(query), "INSERT INTO `chatlog` (`UserID`, `Time`, `Text`) VALUES('%d', NOW(), '%s')", GetPVarInt(playerID, "UserID"), MySQLEscapeString(text));
	mysql_query(query);
}