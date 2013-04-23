CMD:chatmode(playerID, params[], StringID:308(""))
{
	SendClientMessageEx(playerID, COLOR_INFO, StringID:309(""), GetChatModeName(playerID, PVar:playerID[CHATMODE]));
	ShowDialog:ChatMode(playerID);
	return COMMAND_OK;
}