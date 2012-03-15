public IRC_OnUserJoinChannel(botid, channel[], user[], host[])
{
	Count(playerID, maxPlayers)
	{
		FormatNew:string[256](LanguageString(playerID, "%s has joined the IRC channel"), user);
		SendClientMessage(playerID, COLOR_JOINLEAVE, string);
	}
}