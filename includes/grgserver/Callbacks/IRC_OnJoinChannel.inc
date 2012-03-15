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