/**
 * <summary>
 *	Command which gets called by a NPC if something changed (e.g. the NPC recording ended and is not defined as auto repeat).
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which called the command.
 * </param>
 *
 * <param name="params">
 *	The parameters passed to this command.
 * </param>
 *
 * <returns>
 *	<item>COMMAND_OK if the command is valid</item>
 *	<item>COMMAND_ERROR if the command is invalid</item>
 * </returns>
 *
 * <remarks>
 *	This command can only be called by NPCs!
 * </remarks>
 */

NCMD:npccmd(playerID, params[], 0)
{
	new command[256];
	new parameters[256];
	sscanf(params, "ss", command, parameters);
	if (IsStr(command, "reclength"))
	{
		PVar:playerID[NPC_RECORDINGLENGTH] = strval(parameters);
		return COMMAND_OK;
	}
	if (IsStr(command, "recpos"))
	{
		PVar:playerID[NPC_RECORDINGPOSITION] = strval(parameters);
		return COMMAND_OK;
	}
	if (IsStr(command, "stopped"))
	{
		if (PVar:playerID[NPC_RECORDINGSLOT] && PlayNextNPCRecording(playerID))
		{
			return COMMAND_OK;
		}
		if (PVar:playerID[RECORDNPCFORPLAYER] != INVALID_PLAYER_ID)
		{
			new npcs;
			new realPlayerID = PVar:playerID[RECORDNPCFORPLAYER];
			PVar:playerID[RECORDNPCFORPLAYER] = INVALID_PLAYER_ID;
			Kick(playerID);
			SendClientMessageEx(realPlayerID, COLOR_INFO, "76", playerID);
			PlayerLoop(currentPlayerID)
			{
				if (IsPlayerNPC(currentPlayerID) && PVar:currentPlayerID[RECORDNPCFORPLAYER] != INVALID_PLAYER_ID && PVar:currentPlayerID[RECORDNPCFORPLAYER] == realPlayerID)
				{
					npcs++;
				}
			}
			if (npcs)
			{
				SendClientMessageEx(realPlayerID, COLOR_INFO, "77", npcs);
			}
			else
			{
				StopRecordingPlayerData(realPlayerID);
				SendClientMessageEx(realPlayerID, COLOR_INFO, "78");
			}
		}
		return COMMAND_OK;
	}
	return COMMAND_ERROR;
}