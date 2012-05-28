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
 *	The parameters passed to this command (Currently only "stopped" is valid).
 * </param>
 *
 * <returns>
 *	Always returns COMMAND_OK.
 * </returns>
 *
 * <remarks>
 *	This command can only be called by NPCs!
 * </remarks>
 */

NCMD:npccmd(playerID, params[], 0)
{
	if (IsStr(params, "stopped"))
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
			SendClientMessageEx(realPlayerID, COLOR_INFO, 76, playerID);
			PlayerLoop(currentPlayerID)
			{
				if (IsPlayerNPC(currentPlayerID) && PVar:currentPlayerID[RECORDNPCFORPLAYER] != INVALID_PLAYER_ID && PVar:currentPlayerID[RECORDNPCFORPLAYER] == realPlayerID)
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
	return COMMAND_OK;
}