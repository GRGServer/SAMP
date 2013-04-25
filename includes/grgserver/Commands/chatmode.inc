CMD:chatmode(playerID, params[], StringID:308("Change the channel in which your messages should be send"))
{
	SendClientMessageEx(playerID, COLOR_INFO, StringID:309("Current chat channel: %s"), GetChatModeName(playerID, PVar:playerID[CHATMODE]));
	ShowDialog:ChatMode(playerID);
	return COMMAND_OK;
}