NCMD:npccmd(playerid, params[], "Befehle zurück an den Server schicken")
{
	new string[70];
	if (!sscanf(params, "s", string))
	{
		if (!strcmp(string, "stopped", true))
		{
			if (GetPVar:playerid[RECORDNPCFORPLAYER] != INVALID_PLAYER_ID)
			{
				new npcs;
				new realPlayerID = GetPVar:playerid[RECORDNPCFORPLAYER];
				SetPVar:playerid[RECORDNPCFORPLAYER](INVALID_PLAYER_ID);
				Kick(playerid);
				Format:string("Die Wiedergabe von NPC '%s' wurde gestoppt.", GetPlayerNameEx(playerid));
				SendClientMessage(realPlayerID, COLOR_INFO, string);
				Count(playerID, MAX_PLAYERS)
				{
					if (IsPlayerNPC(playerID) && GetPVar:playerID[RECORDNPCFORPLAYER] != INVALID_PLAYER_ID && GetPVar:playerID[RECORDNPCFORPLAYER] == realPlayerID)
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