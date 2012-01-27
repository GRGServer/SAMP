CMD:about(playerid, params[])
{
	SendClientMessage(playerid, COLOR_INFO, "Created by Aerox_Tobi (aerox@grgserver.de) and Programie (programie@selfcoders.com)");
	return COMMAND_OK;
}

// Admin Commands
if(!strcmp(cmd,"/makeadmin",true))
{
	tmp = strtok(cmdtext, idx);
	if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "USAGE: /makeadmin [playerid/PartOfName] [level(1-1337)]");
		return 1;
	}
	new para1;
	new level;
	para1 = ReturnUser(tmp);
	tmp = strtok(cmdtext, idx);
	level = strval(tmp);
	if(GRG_Player[playerid][AdminLevel] == 1338)
	{
		if(para1 != INVALID_PLAYER_ID)
		{
			GetPlayerName(para1, giveplayer, sizeof(giveplayer));
			GetPlayerName(playerid, sendername, sizeof(sendername));
			GRG_Player[para1][AdminLevel] = level;
			printf("AdmCmd: %s hat admin rechte %s gegeben mit level %d.", sendername, giveplayer, level);
			format(string, sizeof(string), "Du hast das Admin Level %d vom Admin %s", level, sendername);
			SendClientMessage(para1, COLOR_LIGHTBLUE, string);
			format(string, sizeof(string), "Du hast gegeben %s das Admin Level %d.", giveplayer,level);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
		}
	}
	else
	{
		SendClientMessage(playerid,COLOR_ERROR."Du bist kein Haupt Admin!");
		return 1;
	}
}