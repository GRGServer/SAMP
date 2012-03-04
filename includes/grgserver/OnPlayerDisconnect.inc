public OnPlayerDisconnect(playerid, reason)
{
	if (!IsPlayerNPC(playerid))
	{
		SavePlayer(playerid);
		FormatNew:string[MAX_PLAYER_NAME + 30]("%s hat den Server verlassen", GetPlayerNameEx(playerid));
		SendClientMessageToAll(COLOR_JOINLEAVE, string);
		IRC_Say(ircBot, IRC_CHANNEL, string);
		TextDrawHideForPlayer(playerid, textDrawSpeedoColumn1);
		TextDrawHideForPlayer(playerid, textDrawClock);
		TextDrawDestroy(textDrawSpeedoName[playerid]);
		TextDrawDestroy(textDrawSpeedoColumn2[playerid]);
		TextDrawDestroy(textDrawRadioStation[playerid]);
	}
	ResetPlayerVariables(playerid);
	return true;
}