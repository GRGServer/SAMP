public IRC_OnConnect(botid, ip[], port)
{
	print("Connected to IRC server");
	IRC_JoinChannel(botid, IRC_CHANNEL);
}