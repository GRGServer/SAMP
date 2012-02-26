public IRC_OnConnect(botid, ip[], port)
{
	print("Connected to IRC server");
	IRC_JoinChannel(botid, IRC_CHANNEL);
}

public IRC_OnDisconnect(botid, ip[], port, reason[])
{
	printf("Disconnected from IRC server: %s", reason);
	print("Reconnecting to IRC server");
	ircBot = IRC_Connect(IRC_HOST, IRC_PORT, IRC_USERNAME, IRC_USERNAME, IRC_USERNAME, IRC_SSL);
}

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

public IRC_OnUserSay(botid, recipient[], user[], host[], message[])
{
	new string[256];
	new userName[MAX_PLAYER_NAME];
	new text[256];
	regex_replace(message, "\\[(.*)\\] (.*)", "\\1", userName, sizeof(userName));
	regex_replace(message, "\\[(.*)\\] (.*)", "\\2", text, sizeof(text));
	if (text[0] == '!')
	{
		if (!strcmp(text, "!help", true))
		{
			IRC_Say(botid, IRC_CHANNEL, "Befehle: !help, !info, !list");
			return true;
		}
		if (!strcmp(text, "!info", true))
		{
			Format:string("Aktuelle Script Revision: %d (%s %s)", COMPILER_SVN_REVISION, COMPILER_DATE, COMPILER_TIME);
			IRC_Say(botid, IRC_CHANNEL, string);
			return true;
		}
		if (!strcmp(text, "!list", true))
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
			Format:string("%d Spieler und %d NPCs online", playersOnline, npcsOnline);
			IRC_Say(botid, IRC_CHANNEL, string);
			return true;
		}
		IRC_Say(botid, IRC_CHANNEL, "Unbekannter Befehl!");
		IRC_Say(botid, IRC_CHANNEL, "Verwende !help um eine Liste der Befehle zu sehen.");
	}
	else
	{
		Format:string("[IRC] %s: %s", userName, text);
		SendClientMessageToAll(COLOR_IRC, string);
		print(string);
		WriteChatToDatabase(INVALID_PLAYER_ID, string);
	}
	return true;
}

public IRC_OnUserJoinChannel(botid, channel[], user[], host[])
{
	new string[256];
	Format:string("%s hat den IRC Channel betreten", user);
	SendClientMessageToAll(COLOR_JOINLEAVE, string);
}

public IRC_OnUserLeaveChannel(botid, channel[], user[], host[], message[])
{
	new string[256];
	Format:string("%s hat den IRC Channel verlassen", user);
	SendClientMessageToAll(COLOR_JOINLEAVE, string);
}