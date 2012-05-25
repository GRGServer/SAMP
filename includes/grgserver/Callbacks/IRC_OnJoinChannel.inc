/**
 * <summary>
 *	Called when a bot joins a channel.
 * </summary>
 *
 * <param name="botid">
 *	The ID of the bot which joined the channel.
 * </param>
 *
 * <param name="channel">
 *	The channel the bot connected to.
 * </param>
 *
 * <remarks>
 *	If the SVN revision has changed since the last server start, a message will be sent to the IRC channel.
 * </remarks>
 */

public IRC_OnJoinChannel(botid, channel[])
{
	if (svnRevisionChanged)
	{
		new string[256];
		Format:string("GRG Server has been updated to r%d by %s", COMPILER_SVN_REVISION, COMPILER_SVN_LASTCOMMITTER);
		IRC_Say(botid, IRC_CHANNEL, string);
	}
	print("IRC channel joined");
}