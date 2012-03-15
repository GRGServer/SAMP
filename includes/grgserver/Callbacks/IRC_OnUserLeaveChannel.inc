public IRC_OnUserLeaveChannel(botid, channel[], user[], host[], message[])
{
	Count(playerID, maxPlayers)
	{
		FormatNew:string[256](LanguageString(playerID, "%s has left the IRC channel"), user);
		SendClientMessage(playerID, COLOR_JOINLEAVE, string);
	}
}