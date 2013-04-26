PCMD:setnpcspawn[NPCADMIN](playerID, params[], StringID:282("Set the spawn position of a NPC"))
{
	new npcName[MAX_PLAYER_NAME];
	if (sscanf(params, "s[" #MAX_PLAYER_NAME "]", npcName))
	{
		CmdUsageMsg(playerID, "setnpcspawn", "Name");
		return COMMAND_USAGE;
	}

	Foreach(arrayIndex, npcs)
	{
		if (!IsStr(npcs[arrayIndex][NPC_NAME], npcName))
		{
			continue;
		}

		GetPlayerPos(playerID, npcs[arrayIndex][NPC_SPAWNPOS][0], npcs[arrayIndex][NPC_SPAWNPOS][1], npcs[arrayIndex][NPC_SPAWNPOS][2]);
		if (IsPlayerInAnyVehicle(playerID))
		{
			GetVehicleZAngle(GetPlayerVehicleID(playerID), npcs[arrayIndex][NPC_SPAWNANGLE]);
		}
		else
		{
			GetPlayerFacingAngle(playerID, npcs[arrayIndex][NPC_SPAWNANGLE]);
		}

		SaveNPCs();

		SendClientMessageEx(playerID, COLOR_INFO, StringID:283("The spawn position of the NPC has been changed"));
		return COMMAND_OK;
	}

	SendClientMessageEx(playerID, COLOR_ERROR, StringID:284("NPC not found!"));
	return COMMAND_ERROR;
}