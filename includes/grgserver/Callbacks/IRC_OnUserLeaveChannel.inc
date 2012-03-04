public IRC_OnUserLeaveChannel(botid, channel[], user[], host[], message[])
{
	new string[256];
	Format:string("%s hat den IRC Channel verlassen", user);
	SendClientMessageToAll(COLOR_JOINLEAVE, string);
}