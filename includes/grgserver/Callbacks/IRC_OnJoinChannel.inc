public IRC_OnJoinChannel(botid, channel[])
{
	if (svnRevisionChanged)
	{
		new string[256];
		Format:string("GRG Server wurde durch %s auf r%d geupdatet", COMPILER_SVN_LASTCOMMITTER, COMPILER_SVN_REVISION);
		IRC_Say(botid, IRC_CHANNEL, string);
	}
	print("IRC channel joined");
}