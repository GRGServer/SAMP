CalculateAge(birthDate)
{
	return (gettime() - birthDate) / 60 / 60 / 24 / 365;
}

CmdUsageMsg(playerID, command[], ...)
{
	new string[256];
	new value[256];
	new parameters;
	parameters = numargs();
	Format:string("Verwendung: /%s", command);
	for (new index = 2; index < parameters; index++)
	{
		GetStringArg(index, value);
		Format:string("%s %s", string, value);
	}
	SendClientMessage(playerID, COLOR_USAGE, string);
}

FormatDate(sqlDateString[], showTime = true)
{
	new date[256];
	new string[256];
	new time[256];
	new day;
	new month;
	new year;
	sscanf(sqlDateString, "ss", date, time);
	sscanf(date, "p-ddd", year, month, day);
	Format:string("%d.%d.%d", year, month, day);
	if (showTime)
	{
		Format:string("%s - %s", string, time);
	}
	return string;
}

FormatTime(seconds)
{
	new string[256];
	new days = seconds / 60 / 60 / 24;
	seconds -= days * 60 * 60 * 24;
	new hours = seconds / 60 / 60;
	seconds -= hours * 60 * 60;
	new minutes = seconds / 60;
	seconds -= minutes * 60;
	Format:string("%d Tage, %s:%s:%s", days, LeadingZero(hours, 0), LeadingZero(minutes, 2), LeadingZero(seconds, 2));
	return string;
}

LeadingZero(value, length)
{
	new string[256];
	new valueString[256];
	valstr(valueString, value);
	new numZeros = strlen(valueString) - length;
	for (new character = 0; character < numZeros; character++)
	{
		Format:string("%s0", string);
	}
	Format:string("%s%s", string, valueString);
	return string;
}

PlayRadioStation(playerID, id)
{
	if (id)
	{
		SetPVarInt(playerID, "RadioOn", true);
		SetPVarInt(playerID, "LastRadioStation", id);
		new name[256];
		Format:name("%s", GetMySQLValue("radiostations", "Name", "ID", val2str(id)));
		PlayAudioStreamForPlayer(playerID, GetMySQLValue("radiostations", "URL", "ID", val2str(id)));
		TextDrawSetString(textDrawRadioStation[playerID], name);
		TextDrawShowForPlayer(playerID, textDrawRadioStation[playerID]);
		new string[256];
		Format:string("Du hörst jetzt %s", name);
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