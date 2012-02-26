CalculateAge(birthDate)
{
	return (gettime() - birthDate) / 60 / 60 / 24 / 365;
}

CmdUsageMsg(playerID, command[], ...)
{
	new value[128 char];
	new parameters;
	parameters = numargs();
	FormatNew:string[128]("Verwendung: /%s", command);
	for (new index = 2; index < parameters; index++)
	{
		GetStringArg(index, value);
		Format:string("%s %s", string, value);
	}
	SendClientMessage(playerID, COLOR_USAGE, string);
}

FormatDate(sqlDateString[], showTime = true)
{
	new string[30];
	new time[10];
	new day;
	new month;
	new year;
	sscanf(sqlDateString, "ss", string, time);
	sscanf(string, "p-ddd", year, month, day);
	Format:string("%02d.%02d.%d", day, month, year);
	if (showTime)
	{
		Format:string("%s - %s", string, time);
	}
	return string;
}

FormatTime(seconds)
{
	new days = seconds / 60 / 60 / 24;
	seconds -= days * 60 * 60 * 24;
	new hours = seconds / 60 / 60;
	seconds -= hours * 60 * 60;
	new minutes = seconds / 60;
	seconds -= minutes * 60;
	FormatNew:string[20]("%d Tage, %02d:%02d:%02d", days, hours, minutes, seconds);
	return string;
}

PlayRadioStation(playerID, id)
{
	if (id)
	{
		SetPVarInt(playerID, "RadioOn", true);
		SetPVarInt(playerID, "LastRadioStation", id);
		FormatNew:string[100]("%s", GetMySQLValue("radiostations", "Name", "ID", val2str(id)));
		PlayAudioStreamForPlayer(playerID, GetMySQLValue("radiostations", "URL", "ID", val2str(id)));
		TextDrawSetString(textDrawRadioStation[playerID], string);
		TextDrawShowForPlayer(playerID, textDrawRadioStation[playerID]);
		Format:string("Du hörst jetzt %s", string);
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
	MySQLQuery("INSERT INTO `chatlog` (`UserID`, `Time`, `Text`) VALUES('%d', NOW(), '%s')", GetUserID(playerID), MySQLEscapeString(text));
}