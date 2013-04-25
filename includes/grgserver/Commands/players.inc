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

PCMD:players[SERVERADMIN](playerID, params[], StringID:619("Show the number of connected players and NPCs"))
{
	new loggedIn;
	LoggedInPlayers(currentPlayerID)
	{
		loggedIn++;
	}
	SendClientMessageEx(playerID, COLOR_INFO, StringID:620("There are currently %d players and %d NPCs online"), GetConnectedPlayers(true, false), GetConnectedPlayers(false, true));
	SendClientMessageEx(playerID, COLOR_INFO, StringID:621("Logged in players: %d"), loggedIn);
	return COMMAND_OK;
}