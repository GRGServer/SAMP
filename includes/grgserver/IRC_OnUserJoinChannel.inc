public IRC_OnUserJoinChannel(botid, channel[], user[], host[])
{
	new string[256];
	Format:string("%s hat den IRC Channel betreten", user);
	SendClientMessageToAll(COLOR_JOINLEAVE, string);
}