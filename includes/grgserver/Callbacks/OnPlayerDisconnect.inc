public OnPlayerDisconnect(playerid, reason)
{
	if (!IsPlayerNPC(playerid))
	{
		if (reason == 1)
		{
			SavePlayer(playerid);
		}
		if (PVar:playerid[FLYCAM])
		{
			KillTimer(PVar:playerid[FLYCAM]);
		}
		PlayerLoop(playerID)
		{
			if (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID) && playerID != playerid)
			{
				SendClientMessageEx(playerid, COLOR_JOINLEAVE, 161, playerid);
			}
		}
		new reasonString[16];
		switch (reason)
		{
			case 0:
			{
				strcat(reasonString, "Timed out");
			}
			case 1:
			{
				strcat(reasonString, "Leaving");
			}
			case 2:
			{
				strcat(reasonString, "Kicked/Banned");
			}
		}
		FormatNew:string[MAX_PLAYER_NAME + 30]("%s has left the server (%s)", GetPlayerNameEx(playerid), reasonString);
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