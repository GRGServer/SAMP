public OnPlayerText(playerid, text[])
{
	FormatNew:string[256]("[%s] %s", GetPlayerNameEx(playerid), text);
	IRC_Say(ircBot, IRC_CHANNEL, string);
	PlayerLoop(playerID)
	{
		if (IsPlayerConnected(playerID))
		{
			if (playerID == playerid)
			{
				SendClientMessage(playerID, COLOR_CHATOWN, string);
			}
			else
			{
				SendClientMessage(playerID, COLOR_CHAT, string);
			}
		}
	}
	WriteChatToDatabase(playerid, text);
	return false;
}