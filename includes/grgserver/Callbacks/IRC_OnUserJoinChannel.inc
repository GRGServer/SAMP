/**
 * <summary>
 *	Called when a user joins a common channel.
 * </summary>
 *
 * <param name="botid">
 *	The ID of the bot which gots notified of the join event.
 * </param>
 *
 * <param name="channel">
 *	The channel where the user joined.
 * </param>
 *
 * <param name="user">
 *	The name of the joined user.
 * </param>
 *
 * <param name="host">
 *	The host name of the joined user.
 * </param>
 *
 * <remarks>
 *	The callback sends a message to all currently connected players.
 * </remarks>
 */

public IRC_OnUserJoinChannel(botid, channel[], user[], host[])
{
	PlayerLoop(playerID)
	{
		SendClientMessageEx(playerID, COLOR_JOINLEAVE, 2, user);
	}
}