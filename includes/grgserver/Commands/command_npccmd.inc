NCMD:npccmd(playerid, params[], "Befehle zurück an den Server schicken")
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
				Format:string("Die Wiedergabe von NPC '%s' wurde gestoppt.", GetPlayerNameEx(playerid));
				SendClientMessage(realPlayerID, COLOR_INFO, string);
				Count(playerID, MAX_PLAYERS)
				{
					if (IsPlayerNPC(playerID) && PVar:playerID[RECORDNPCFORPLAYER] != INVALID_PLAYER_ID && PVar:playerID[RECORDNPCFORPLAYER] == realPlayerID)
					{
						npcs++;
					}
				}
				if (npcs)
				{
					Format:string("Es werden noch %d weitere NPCs für diese Aufnahme verwendet.", npcs);
					SendClientMessage(realPlayerID, COLOR_INFO, string);
				}
				else
				{
					StopRecordingPlayerData(realPlayerID);
					SendClientMessage(realPlayerID, COLOR_INFO, "Der letzte NPC hat die Aufnahme gestoppt!");
				}
			}
		}
	}
	return COMMAND_OK;
}