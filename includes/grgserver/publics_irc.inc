public IRC_OnConnect(botid, ip[], port)
{
	print("Connected to IRC server");
	IRC_JoinChannel(botid, IRC_CHANNEL);
}

public IRC_OnJoinChannel(botid, channel[])
{
	print("IRC channel joined");
	IRC_Say(botid, channel, "Hello!");
	IRC_Say(botid, channel, "I'm an IRC chat relay for GRG Server.");
}

public IRC_OnUserSay(botid, recipient[], user[], host[], message[])
{
	new string[256];
	format(string, sizeof(string), "[IRC] %s: %s", user, message);
	SendClientMessageToAll(COLOR_IRC, string);
	writeChatToDatabase(INVALID_PLAYERID, string);
}