public IRC_OnConnect(botid, ip[], port)
{
	print("Connected to IRC server");
	IRC_JoinChannel(botid, IRC_CHANNEL);
}

public IRC_OnJoinChannel(botid, channel[])
{
	new string[256];
	print("IRC channel joined");
	IRC_Say(botid, channel, "Hello!");
	IRC_Say(botid, channel, "I'm an IRC chat relay for GRG Server.");
	format(string, sizeof(string), "Current running SVN revision: %d", COMPILER_SVN_REVISION);
	IRC_Say(botid, channel, string);
}

public IRC_OnUserSay(botid, recipient[], user[], host[], message[])
{
	new string[256];
	if (!strcmp(message[0], "!", true))
	{
		if (!strcmp(message, "!help", true))
		{
			IRC_Say(botid, user, "Befehle: !help, !list");
			return true;
		}
		if (!strcmp(message, "!list", true))
		{
			new npcsOnline;
			new playersOnline;
			for (new playerID; playerID < MAX_PLAYERS; playerID++)
			{
				if (IsPlayerConnected(playerID))
				{
					if (IsPlayerNPC(playerID))
					{
						npcsOnline++;
					}
					else
					{
						playersOnline++;
					}
				}
			}
			format(string, sizeof(string), "%d Spieler und %d NPCs online", playersOnline, npcsOnline);
			IRC_Say(botid, user, string);
			return true;
		}
		IRC_Say(botid, user, "Unbekannter Befehl!");
		IRC_Say(botid, user, "Verwende !help um eine Liste der Befehle zu sehen.");
	}
	else
	{
		format(string, sizeof(string), "[IRC] %s: %s", user, message);
		SendClientMessageToAll(COLOR_IRC, string);
		writeChatToDatabase(INVALID_PLAYERID, string);
	}
	return true;
}