/**
 * <summary>
 *	Called when a user sends a message to a common channel or a private message to a bot.
 * </summary>
 *
 * <param name="botid">
 *	The ID of the bot which received the message.
 * </param>
 *
 * <param name="recipient">
 *	The bot name or the channel name which received the message.
 * </param>
 *
 * <param name="user">
 *	Name of the user which sent the message.
 * </param>
 *
 * <param name="host">
 *	Host of the user which sent the message.
 * </param>
 *
 * <param name="message">
 *	The message which was sent by the user.
 * </param>
 */

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
			IRC_Say(botid, IRC_CHANNEL, "Commands: !help, !info, !list");
			return true;
		}
		if (!strcmp(text, "!info", true))
		{
			Format:string("Current script revision: %d (%s %s)", COMPILER_SVN_REVISION, COMPILER_DATE, COMPILER_TIME);
			IRC_Say(botid, IRC_CHANNEL, string);
			return true;
		}
		if (!strcmp(text, "!list", true))
		{
			new npcsOnline;
			new playersOnline;
			PlayerLoop(playerID)
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
			Format:string("%d players and %d NPCs are online", playersOnline, npcsOnline);
			IRC_Say(botid, IRC_CHANNEL, string);
			return true;
		}
		IRC_Say(botid, IRC_CHANNEL, "Unknown command!");
		IRC_Say(botid, IRC_CHANNEL, "Use !help to see a list of commands.");
	}
	else
	{
		Format:string("[IRC] %s: %s", userName, text);
		MySQLQuery("INSERT INTO `chatlog` (`channel`, `time`, `text`) VALUES('ALL', NOW(), '%s')", MySQLEscapeString(string));
		SendClientMessageToAll(COLOR_IRC, string);
		print(string);
	}
	return true;
}