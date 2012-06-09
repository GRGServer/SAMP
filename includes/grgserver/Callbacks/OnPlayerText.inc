public OnPlayerText(playerid, text[])
{
	new targetPlayerID = INVALID_PLAYER_ID;
	if (IsStr(PVar:playerid[CHATMODE], "PLAYER"))
	{
		targetPlayerID = GetPlayerByUserID(PVar:playerid[CHATMODE_USERID]);
	}
	SendMessageToChannel(playerid, PVar:playerid[CHATMODE], text, targetPlayerID);
	return false;
}