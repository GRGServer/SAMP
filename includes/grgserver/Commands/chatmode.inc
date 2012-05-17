CMD:chatmode(playerID, params[], 308)
{
	SendClientMessageEx(playerID, COLOR_INFO, 309, GetChatModeName(playerID, PVar:playerID[CHATMODE]));
	ShowDialog:ChatMode(playerID);
	return COMMAND_OK;
}