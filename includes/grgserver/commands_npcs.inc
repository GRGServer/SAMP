NCMD:npccmd(playerid, params[], "Befehle zurück an den Server schicken")
{
	new command[256];
	if (!sscanf(params, "s", command))
	{
		if (!strcmp(command, "stopped", true))
		{
			if (GetPVarType(playerid, "RecordNPCForPlayer") == PLAYER_VARTYPE_INT)
			{
				new string[256];
				new npcs;
				new realPlayerID = GetPVarInt(playerid, "RecordNPCForPlayer");
				DeletePVar(playerid, "RecordNPCForPlayer");
				Kick(playerid);
				Format:string("Die Wiedergabe von NPC '%s' wurde gestoppt.", GetPlayerNameEx(playerid));
				SendClientMessage(realPlayerID, COLOR_INFO, string);
				for (new playerID; playerID < MAX_PLAYERS; playerID++)
				{
					if (IsPlayerNPC(playerID))
					{
						if (GetPVarType(playerID, "RecordNPCForPlayer") == PLAYER_VARTYPE_INT)
						{
							if (GetPVarInt(playerID, "RecordNPCForPlayer") == realPlayerID)
							{
								npcs++;
							}
						}
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