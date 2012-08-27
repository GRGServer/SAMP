/**
 * <summary>
 *	Show the number of connected players and NPCs.
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

PCMD:players[SERVERADMIN](playerID, params[], 619)
{
	new loggedIn;
	LoggedInPlayers(currentPlayerID)
	{
		loggedIn++;
	}
	SendClientMessageEx(playerID, COLOR_INFO, 620, GetConnectedPlayers(true, false), GetConnectedPlayers(false, true));
	SendClientMessageEx(playerID, COLOR_INFO, 621, loggedIn);
	return COMMAND_OK;
}