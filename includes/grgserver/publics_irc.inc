public IRC_OnConnect(botid, ip[], port)
{
	IRC_JoinChannel(botid, IRC_CHANNEL);
}

public IRC_OnJoinChannel(botid, channel[])
{
	IRC_Say(botid, channel, "Hello!");
	IRC_Say(botid, channel, "I'm an IRC chat relay for the SAMP-Server 'GRGServer'.");
}