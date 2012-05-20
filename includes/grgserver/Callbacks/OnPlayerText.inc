public OnPlayerText(playerid, text[])
{
	SendMessageToChannel(playerid, PVar:playerid[CHATMODE], text);
	return false;
}