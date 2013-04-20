/**
 * <summary>
 *	Show information about the server.
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

CMD:about(playerID, params[], 86)
{
	SendClientMessageEx(playerID, COLOR_INFO, "85");
	return COMMAND_OK;
}