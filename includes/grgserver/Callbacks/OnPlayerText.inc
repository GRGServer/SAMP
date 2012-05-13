public OnPlayerText(playerid, text[])
{
	new string[256];
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	GetPlayerPos(playerid, posX, posY, posZ);
	PlayerLoop(playerID)
	{
		if (IsPlayerConnected(playerID))
		{
			switch (PVar:playerid[CHATMODE])
			{
				case CHATMODE_ADMINS:
				{
					if (permissions[playerID][PERMISSION_ADMIN] || playerID == playerid)
					{
						Format:string("[%s@Admins] %s", GetPlayerNameEx(playerid), text);
						SendClientMessage(playerID, COLOR_CHAT_ADMINS, string);
					}
				}
				case CHATMODE_ALL:
				{
					Format:string("[%s@%s] %s", GetPlayerNameEx(playerid), LanguageString(playerID, 310), text);
					SendClientMessage(playerID, COLOR_CHAT_ALL, string);
				}
				case CHATMODE_INRANGE:
				{
					new Float:distance = GetPlayerDistanceFromPoint(playerID, posX, posY, posZ);
					if (distance <= CHAT_MAXDISTANCE)
					{
						Format:string("[%s] %s", GetPlayerNameEx(playerid), text);
						SendClientMessage(playerID, COLOR_CHAT_INRANGE, string);
					}
				}
				case CHATMODE_JOB:
				{
					if (PVar:playerid[JOBID] == PVar:playerID[JOBID])
					{
						Format:string("[%s@Job] %s", GetPlayerNameEx(playerid), text);
						SendClientMessage(playerID, COLOR_CHAT_JOB, string);
					}
				}
			}
		}
	}
	if (PVar:playerid[CHATMODE] == CHATMODE_ALL)
	{
		Format:string("[%s] %s", GetPlayerNameEx(playerid), text);
		IRC_Say(ircBot, IRC_CHANNEL, string);
	}
	WriteChatToDatabase(playerid, text);
	return false;
}