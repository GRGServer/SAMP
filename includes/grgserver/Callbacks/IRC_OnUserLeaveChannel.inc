/**
 * <summary>
 *	Called when a user parts a common channel.
 * </summary>
 *
 * <param name="botid">
 *	The ID of the bot which gots notified of the leave event.
 * </param>
 *
 * <param name="channel">
 *	The channel which the user left.
 * </param>
 *
 * <param name="user">
 *	The name of the user which left the channel.
 * </param>
 *
 * <param name="host">
 *	The host name of the user which left the channel.
 * </param>
 *
 * <param name="message">
 *	The message the user sent to all users on left.
 * </param>
 *
 * <remarks>
 *	The callback sends a message to all currently connected players.
 * </remarks>
 */

public IRC_OnUserLeaveChannel(botid, channel[], user[], host[], message[])
{
	PlayerLoop(playerID)
	{
		SendClientMessageEx(playerID, COLOR_JOINLEAVE, 4, user);
	}
}