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

PCMD:controlnpc[NPCADMIN](playerID, params[], StringID:100("Control NPCs (e.g. start or stop)"))
{
	new command[256];
	new targetPlayerName[MAX_PLAYER_NAME];
	if (sscanf(params, "s[" #MAX_PLAYER_NAME "]s[256]", targetPlayerName, command))
	{
		CmdUsageMsg(playerID, "controlnpc", "Playername", "Command");
		SendClientMessageEx(playerID, COLOR_INFO, StringID:124("recordingName, playbackType and autoRepeat  is only required for the command 'start'."));
		return COMMAND_USAGE;
	}
	if (!strcmp(command, "connect", true))
	{
		SendClientMessageEx(playerID, COLOR_INFO, StringID:125("NPC connected"));
		ConnectNPC(targetPlayerName, NPC_SCRIPTNAME);
		return COMMAND_OK;
	}
	if (GetPlayerID(targetPlayerName) != INVALID_PLAYER_ID)
	{
		new npcPlayerID = GetPlayerID(targetPlayerName);
		if (IsStr(command, "status"))
		{
			SendClientMessageEx(playerID, COLOR_INFO, StringID:624("Current recording position: %d sec"), PVar:npcPlayerID[NPC_RECORDINGPOSITION]);
			SendClientMessageEx(playerID, COLOR_INFO, StringID:606("Recording length: %d sec"), PVar:npcPlayerID[NPC_RECORDINGLENGTH]);
			return COMMAND_OK;
		}
		SendClientMessageEx(playerID, COLOR_INFO, StringID:123("Command sent: %s"), command);
		SendNPCCommand(npcPlayerID, command);
		return COMMAND_OK;
	}
	else
	{
		return COMMAND_PLAYER_NOT_FOUND;
	}
}