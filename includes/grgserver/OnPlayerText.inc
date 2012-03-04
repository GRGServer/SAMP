public OnPlayerText(playerid, text[])
{
	FormatNew:string[256]("[%s] %s", GetPlayerNameEx(playerid), text);
	IRC_Say(ircBot, IRC_CHANNEL, string);
	SendClientMessageToAllExcept(playerid, COLOR_CHAT, string);
	SendClientMessage(playerid, COLOR_CHATOWN, string);
	WriteChatToDatabase(playerid, text);
	return false;
}