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

CMD:about(playerID, params[], StringID:86("Information about this script"))
{
	SendClientMessageEx(playerID, COLOR_INFO, StringID:85("Created by Aerox_Tobi (aerox@grgserver.net) and Programie (programie@selfcoders.com)"));
	return COMMAND_OK;
}