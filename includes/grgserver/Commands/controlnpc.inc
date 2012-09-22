/**
 * <summary>
 *	Control a NPC.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which called the command.
 * </param>
 *
 * <param name="params">
 *	<title>The parameters passed to this command.</title>
 *	<item>NPC name</item>
 *	<item>Command (pause, resume, setrec, start, stop or teleport)</item>
 *	<item>Parameters for the command (Not required by all commands)</item>
 * </param>
 *
 * <returns>
 *	<item>COMMAND_OK</item>
 *	<item>COMMAND_PLAYER_NOT_FOUND</item>
 *	<item>COMMAND_USAGE</item>
 * </returns>
 */

PCMD:controlnpc[NPCADMIN](playerID, params[], 100)
{
	new command[256];
	new targetPlayerName[MAX_PLAYER_NAME];
	if (sscanf(params, "ss", targetPlayerName, command))
	{
		CmdUsageMsg(playerID, "controlnpc", "Playername", "Command");
		SendClientMessageEx(playerID, COLOR_INFO, 124);
		return COMMAND_USAGE;
	}
	if (!strcmp(command, "connect", true))
	{
		SendClientMessageEx(playerID, COLOR_INFO, 125);
		ConnectNPC(targetPlayerName, NPC_SCRIPTNAME);
		return COMMAND_OK;
	}
	if (GetPlayerID(targetPlayerName) != INVALID_PLAYER_ID)
	{
		new npcPlayerID = GetPlayerID(targetPlayerName);
		if (IsStr(command, "status"))
		{
			SendClientMessageEx(playerID, COLOR_INFO, 624, PVar:npcPlayerID[NPC_RECORDINGPOSITION]);
			SendClientMessageEx(playerID, COLOR_INFO, 606, PVar:npcPlayerID[NPC_RECORDINGLENGTH]);
			return COMMAND_OK;
		}
		SendClientMessageEx(playerID, COLOR_INFO, 123, command);
		SendNPCCommand(npcPlayerID, command);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}