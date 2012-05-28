/**
 * <summary>
 *	Restart the gamemode.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which called the command.
 * </param>
 *
 * <param name="params">
 *	The parameters passed to this command (Unused).
 * </param>
 *
 * <returns>
 *	Always returns COMMAND_OK.
 * </returns>
 */

PCMD:gmx[SERVERADMIN](playerID, params[], 105)
{
	if (GetConnectedPlayers(true, false) > 1)
	{
		ShowDialog:RestartGamemode(playerID);
	}
	else
	{
		printf("%s has restarted the gamemode", GetPlayerNameEx(playerID));
		SendRconCommand("gmx");
	}
	return COMMAND_OK;
}