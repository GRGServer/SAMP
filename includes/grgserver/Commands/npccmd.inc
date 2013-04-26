/**
 * <summary>
 *	Command which gets called by a NPC if something changed.
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

NCMD:npccmd(playerID, params[], StringID:9("Report status to the server"))
{
	new command[256];
	new parameters[256];
	sscanf(params, "s[256]s[256]", command, parameters);

	new npcName[MAX_PLAYER_NAME];
	GetPlayerName(playerID, npcName, sizeof(npcName));

	Foreach(arrayIndex, npcs)
	{
		if (IsStr(npcs[arrayIndex][NPC_NAME], npcName))
		{
			if (IsStr(command, "reclength"))
			{
				npcs[arrayIndex][NPC_RECORDINGLENGTH] = strval(parameters);
				return COMMAND_OK;
			}
			break;
		}
	}

	return COMMAND_ERROR;
}