PCMD:addstaticnpc[NPCADMIN](playerID, params[], StringID:97("Place a NPC without recording at your current position"))
{
	new npcName[MAX_PLAYER_NAME];
	if (sscanf(params, "s[" #MAX_PLAYER_NAME "]", npcName))
	{
		CmdUsageMsg(playerID, "addstaticnpc", "Name");
		return COMMAND_USAGE;
	}

	Foreach(arrayIndex, npcs)
	{
		if (StrNotNull(npcs[arrayIndex][NPC_NAME]))
		{
			continue;
		}

		strcat(npcs[arrayIndex][NPC_NAME], npcName, MAX_PLAYER_NAME);
		GetPlayerPos(playerID, npcs[arrayIndex][NPC_SPAWNPOS][0], npcs[arrayIndex][NPC_SPAWNPOS][1], npcs[arrayIndex][NPC_SPAWNPOS][2]);
		GetPlayerFacingAngle(playerID, npcs[arrayIndex][NPC_SPAWNANGLE]);

		ConnectNPC(npcName, NPC_SCRIPTNAME);
		SaveNPCs();

		SendClientMessageEx(playerID, COLOR_INFO, StringID:2("The NPC has been added"));
		return COMMAND_OK;
	}

	SendClientMessageEx(playerID, COLOR_ERROR, StringID:4("No more free NPC slots available! Increase MAX_NPCS and try again"));
	return COMMAND_ERROR;
}