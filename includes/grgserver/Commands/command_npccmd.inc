NCMD:npccmd(playerid, params[], 0)
{
	new string[70];
	if (!sscanf(params, "s", string))
	{
		if (!strcmp(string, "stopped", true))
		{
			if (PVar:playerid[RECORDNPCFORPLAYER] != INVALID_PLAYER_ID)
			{
				new npcs;
				new realPlayerID = PVar:playerid[RECORDNPCFORPLAYER];
				PVar:playerid[RECORDNPCFORPLAYER] = INVALID_PLAYER_ID;
				Kick(playerid);
				SendClientMessageEx(realPlayerID, COLOR_INFO, 76, playerid);
				PlayerLoop(playerID)
				{
					if (IsPlayerNPC(playerID) && PVar:playerID[RECORDNPCFORPLAYER] != INVALID_PLAYER_ID && PVar:playerID[RECORDNPCFORPLAYER] == realPlayerID)
					{
						npcs++;
					}
				}
				if (npcs)
				{
					SendClientMessageEx(realPlayerID, COLOR_INFO, 77, npcs);
				}
				else
				{
					StopRecordingPlayerData(realPlayerID);
					SendClientMessageEx(realPlayerID, COLOR_INFO, 78);
				}
			}
		}
	}
	return COMMAND_OK;
}