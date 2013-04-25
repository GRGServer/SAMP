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

PCMD:gmx[SERVERADMIN](playerID, params[], StringID:105("Restart game mode"))
{
	if (GetConnectedPlayers(true, false) > 1)
	{
		ShowDialog:RestartGamemode(playerID);
	}
	else
	{
		RestartGameMode(playerID, "No more players, no reason");
	}
	return COMMAND_OK;
}