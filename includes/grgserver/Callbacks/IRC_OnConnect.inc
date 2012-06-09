/**
 * <summary>
 *	Called when a bot successfully connects to the IRC server.
 * </summary>
 *
 * <param name="botid">
 *	The ID of the connected bot.
 * </param>
 *
 * <param name="ip">
 *	Unknown
 * </param>
 *
 * <param name="port">
 *	Unknown
 * </param>
 *
 * <remarks>
 *	The bot joins the configured channel once this callback gets called.
 * </remarks>
 */

public IRC_OnConnect(botid, ip[], port)
{
	print("Connected to IRC server");
	IRC_JoinChannel(botid, ircChannel);
}