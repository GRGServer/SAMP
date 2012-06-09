/**
 * <summary>
 *	Called when a bot disconnects from the IRC server.
 * </summary>
 *
 * <param name="botid">
 *	The ID of the disconnected bot.
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
 * <param name="reason">
 *	Reason for the disconnect (e.g. normal leaving the server or get kicked)
 * </param>
 *
 * <remarks>
 *	The IRC bot tries to reconnect to the IRC server once this callback gets called.
 * </remarks>
 */

public IRC_OnDisconnect(botid, ip[], port, reason[])
{
	printf("Disconnected from IRC server: %s", reason);
	if (serverType == SERVER_PUBLIC)
	{
		ircBot = IRC_Connect(IRC_HOST, IRC_PORT, IRC_PUBLIC_USERNAME, IRC_PUBLIC_USERNAME, IRC_PUBLIC_USERNAME, IRC_SSL);
	}
	else
	{
		ircBot = IRC_Connect(IRC_HOST, IRC_PORT, IRC_DEV_USERNAME, IRC_DEV_USERNAME, IRC_DEV_USERNAME, IRC_SSL);
	}
}