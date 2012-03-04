public IRC_OnDisconnect(botid, ip[], port, reason[])
{
	printf("Disconnected from IRC server: %s", reason);
	print("Reconnecting to IRC server");
	ircBot = IRC_Connect(IRC_HOST, IRC_PORT, IRC_USERNAME, IRC_USERNAME, IRC_USERNAME, IRC_SSL);
}