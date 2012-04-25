CMD:chatmode(playerID, params[], 308)
{
	SendClientMessageEx(playerID, COLOR_INFO, 309, GetChatModeName(playerID, PVar:playerID[CHATMODE]));
	ShowDialog(playerID, DIALOG_CHATMODE);
	return COMMAND_OK;
}