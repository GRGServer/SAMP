public OnPlayerDisconnect(playerid, reason)
{
	if (!IsPlayerNPC(playerid))
	{
		SavePlayer(playerid);
		
		PlayerLoop(playerID)
		{
			if (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID) && playerID != playerid)
			{
				SendClientMessageEx(playerid, COLOR_JOINLEAVE, 161, playerid);
			}
		}
		FormatNew:string[MAX_PLAYER_NAME + 30]("%s has left the server", GetPlayerNameEx(playerid));
		IRC_Say(ircBot, IRC_CHANNEL, string);
		PlayerTextDrawDestroy(playerid, PTextDraw:playerid[RADIOSTATION]);
		PlayerTextDrawDestroy(playerid, PTextDraw:playerid[SPEEDO_COLUMN1]);
		PlayerTextDrawDestroy(playerid, PTextDraw:playerid[SPEEDO_COLUMN2]);
		PlayerTextDrawDestroy(playerid, PTextDraw:playerid[VEHICLENAME]);
		PlayerTextDrawDestroy(playerid, PTextDraw:playerid[SCREENFADER]);
		SendDeathMessage(INVALID_PLAYER_ID, playerid, 201);
	}
	StopAudioStreamForPlayer(playerid);
	ResetPlayerVariables(playerid);
	return true;
}