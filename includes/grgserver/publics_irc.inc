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
	print("IRC channel joined");
}

public IRC_OnUserSay(botid, recipient[], user[], host[], message[])
{
	new string[256];
	if (message[0] == '!')
	{
		if (!strcmp(message, "!help", true))
		{
			IRC_Say(botid, user, "Befehle: !help, !info, !list");
			return true;
		}
		if (!strcmp(message, "!info", true))
		{
			format(string, sizeof(string), "Aktuelle Script Revision: %d (%s %s)", COMPILER_SVN_REVISION, COMPILER_DATE, COMPILER_TIME);
			IRC_Say(botid, user, string);
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

public IRC_OnUserJoinChannel(botid, channel[], user[], host[])
{
	new string[256];
	format(string, sizeof(string), "%s hat den IRC Channel betreten", user);
	SendClientMessageToAll(COLOR_JOINLEAVE, string);
}

public IRC_OnUserLeaveChannel(botid, channel[], user[], host[], message[])
{
	new string[256];
	format(string, sizeof(string), "%s hat den IRC Channel verlassen", user);
	SendClientMessageToAll(COLOR_JOINLEAVE, string);
}