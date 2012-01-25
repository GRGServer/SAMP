#include <a_samp>
#include <mysql>

#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_RED 0xAA3333AA

#define LoginDialog 1
#define RegisterDialog 2
#define ErrorDialog 3

#define SQL_HOST   "localhost"
#define SQL_USER   "grgserver"
#define SQL_PASS   "2RuvHtYb7KRh6PVt"
#define SQL_DATA   "grgserver"


enum Info
{
	Name[MAX_PLAYER_NAME],
	Key[128],
	Level,
	AdminLevel,
};
new GRG_Player[MAX_PLAYERS][Info];


main()
{
	print("\n----------------------------------");
	print("GRG Server");
	print("----------------------------------\n");
}

public OnGameModeInit()
{
	mysql_init();
    mysql_connect(SQL_HOST, SQL_USER, SQL_DATA, SQL_PASS);
	SetGameModeText("GRG Server");
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	return 1;
}

public OnGameModeExit()
{
	mysql_close();
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

public OnPlayerConnect(playerid)
{
 	if(mysql_CheckAccount(playerid) == 0)
	{
        SendClientMessage(playerid,COLOR_YELLOW, "Script edit by Aerox_Tobi and Programie ");
        ShowPlayerDialog(playerid,RegisterDialog, DIALOG_STYLE_INPUT, "Register", "Du bist noch nicht Registriert!\r\nGib hier dein passwort ein.", "Fertig", "Abbrechen");
		return 1;
    }
    else if(mysql_CheckAccount(playerid) == 1)
    {
		SendClientMessage(playerid, COLOR_YELLOW,"Scripting By Aerox_Tobi and Programie");
		ShowPlayerDialog(playerid,LoginDialog,DIALOG_STYLE_INPUT,"Login","Deine Daten wurden Gefunden\n\nGeb hier dien Passwort ein!","Eintretten","Abbrechen");
		return 1;
    }
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new cmd[256];
//	new tmp[256];
	new idx;
	cmd = strtok(inputtext, idx);
	if(strval(inputtext))
	{
		if(dialogid == LoginDialog)
	   	{
			if(response == 0)
	        {
				SendClientMessage(playerid,COLOR_RED,"Du kannst nun das Spiel Beenden!");
				Kick(playerid);
			}
			if(response == 1)
			{
	        	if(strlen(inputtext) == 0)
	            {
	            	ShowPlayerDialog(playerid,LoginDialog,DIALOG_STYLE_INPUT,"Login","Das Angegebene Passwort war Falsch.\nBitte log dich jetzt mit dem richtigen Passwort ein:","Login","Abbrechen");
	                return 1;
	            }
	            else
	            {
	            	new SpielerName[MAX_PLAYER_NAME];
	                GetPlayerName(playerid, SpielerName, MAX_PLAYER_NAME);
	                if(!strcmp(inputtext, mysql_ReturnPasswort(SpielerName), true))
	                {
	                	SetPVarInt(playerid,"Eingeloggt",1);
	                    LoadPlayer(playerid);
	                    SpawnPlayer(playerid);
	                    return 1;
	                }
	                else
	                {
	                	ShowPlayerDialog(playerid,LoginDialog,DIALOG_STYLE_INPUT,"Login","Das war das Falsche Passwort.\nBitte log dich jetzt mit dem richtigen Passwort ein:","Login","Abbrechen");
	                    return 1;
	                }
	            }
			}
		}
		if(dialogid == RegisterDialog)
        {
			if(response == 0)
	        {
	            SendClientMessage(playerid,COLOR_RED,"Du kannst nun SAMP beenden!");
	            Kick(playerid);
			}
			if(response == 1)
			{
   				if(strlen(inputtext) == 0)
	            {
	            	ShowPlayerDialog(playerid,RegisterDialog,DIALOG_STYLE_INPUT,"Register","Das angegebene Passwort war zu Kurz...\nBitte Registrier dich jetzt mit einem Passwort:","Register","Abbrechen");
	            	return 1;
	            }
	            else
	            {
	            	CreateAccount(playerid, inputtext);
	                SetPVarInt(playerid,"Eingeloggt",1);
	                SpawnPlayer(playerid);
	                return 1;
	            }
	        }
		}
	}
	return 1;
}

public OnPlayerSpawn(playerid)
{
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (!strcmp("/admins",cmdtext,true,10))
	{

		return 1;
	}
	return 0;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}

stock mysql_SetInt(Table[], Field[], To, Where[], Where2[])
{
    new query[128];
    mysql_real_escape_string(Table, Table);
    mysql_real_escape_string(Field, Field);
    mysql_real_escape_string(Where, Where);
    mysql_real_escape_string(Where2, Where2);
    format(query, 128, "UPDATE `%s` SET `%s` = '%d' WHERE `%s` = '%s'", Table, Field, To, Where, Where2);
    mysql_query(query);
    return true;
}
stock mysql_SetString(Table[], Field[], To[], Where[], Where2[])
{
    new query[128];
    mysql_real_escape_string(Table, Table);
    mysql_real_escape_string(Field, Field);
    mysql_real_escape_string(To, To);
    mysql_real_escape_string(Where, Where);
    mysql_real_escape_string(Where2, Where2);
    format(query, 128, "UPDATE `%s` SET `%s` = '%s' WHERE `%s` = '%s'", Table, Field, To, Where, Where2);
    mysql_query(query);
    return true;
}
stock mysql_SetFloat(Table[], Field[], Float:To, Where[], Where2[])
{
    new query[128];
    mysql_real_escape_string(Table, Table);
    mysql_real_escape_string(Field, Field);
    mysql_real_escape_string(Where, Where);
    mysql_real_escape_string(Where2, Where2);
    format(query, 128, "UPDATE `%s` SET `%s` = '%.1f' WHERE `%s` = '%s'", Table, Field, To, Where, Where2);
    mysql_query(query);
    return true;
}

stock Float:mysql_GetFloat(Table[], Field[], Where[], Is[])
{
    new query[128], Float:sqlfloat;
    mysql_real_escape_string(Table, Table);
    mysql_real_escape_string(Field, Field);
    mysql_real_escape_string(Where, Where);
    mysql_real_escape_string(Is, Is);
    format(query, 128, "SELECT `%s` FROM `%s` WHERE `%s` = '%s'", Field, Table, Where, Is);
    mysql_query(query);
    mysql_store_result();
    mysql_fetch_float(sqlfloat);
    mysql_free_result();
    return sqlfloat;
}



stock mysql_GetString(Table[], Field[], Where[], Is[])
{
    new query[128], Get[128];
    mysql_real_escape_string(Table, Table);
    mysql_real_escape_string(Field, Field);
    mysql_real_escape_string(Where, Where);
    mysql_real_escape_string(Is, Is);
    format(query, 128, "SELECT `%s` FROM `%s` WHERE `%s` = '%s'", Field, Table, Where, Is);
    mysql_query(query);
    mysql_store_result();
    mysql_fetch_row(Get);
    return Get;
}

stock mysql_GetInt(Table[], Field[], Where[], Is[])
{
    new query[128];
    mysql_real_escape_string(Table, Table);
    mysql_real_escape_string(Field, Field);
    mysql_real_escape_string(Where, Where);
    mysql_real_escape_string(Is, Is);
    format(query, 128, "SELECT `%s` FROM `%s` WHERE `%s` = '%s'", Field, Table, Where, Is);
    mysql_query(query);
    mysql_store_result();
    new sqlint = mysql_fetch_int();
    mysql_free_result();
    return sqlint;
}

stock mysql_ReturnPasswort(pName[])
{
    new query[130], Get[130];
    mysql_real_escape_string(pName, pName);
    format(query, 128, "SELECT `Password` FROM `users` WHERE `Username` = '%s'", pName);
    mysql_query(query);
    mysql_store_result();
    mysql_fetch_row(Get);
    mysql_free_result();
    return Get;
}

stock SavePlayer(playerid)
{
    if(IsPlayerConnected(playerid) && !IsPlayerNPC(playerid))
    {
        if(GetPVarInt(playerid,"Eingeloggt") == 1)
        {
            mysql_SetInt("players", "Level", GRG_Player[playerid][Level], "Username", GRG_Player[playerid][Name]);
            mysql_SetInt("players", "AdminLevel", GRG_Player[playerid][AdminLevel], "Username", GRG_Player[playerid][Name]);
		}
    }
    return 1;
}

stock LoadPlayer(playerid)
{
    if(IsPlayerConnected(playerid) && !IsPlayerNPC(playerid))
    {
        GetPlayerName(playerid,GRG_Player[playerid][Name],MAX_PLAYER_NAME);
        GRG_Player[playerid][Level] = mysql_GetInt("users", "Level","Username",GRG_Player[playerid][Name]);
		GRG_Player[playerid][AdminLevel] = mysql_GetInt("users", "AdminLevel", "Username",GRG_Player[playerid][Name]);
		SendClientMessage(playerid,COLOR_YELLOW,"Klicke nun auf Spawn!");
	}
    return 1;
}

stock CreateAccount(playerid, pass[])
{
    new query[1024];
	new lName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, lName, MAX_PLAYER_NAME);
    mysql_real_escape_string(lName,lName);
    mysql_real_escape_string(pass,pass);
    printf("Hier ist er registriert");
    format(query, sizeof(query), "INSERT INTO `users` (`Username`,`Password`,`Level`,`AdminLevel`) VALUE ('%d','%s','%s','%d','%d')",lName,pass,GRG_Player[playerid][Level],GRG_Player[playerid][AdminLevel]);
    mysql_query(query);
    SavePlayer(playerid);
    printf("Er hat nun Registriert");
	SendClientMessage(playerid,COLOR_YELLOW,"Tippe nun /login und dein Passwort!");
    return true;
}

stock mysql_CheckAccount(playerid)
{
    new Query[128];
	new hName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, hName, MAX_PLAYER_NAME);
    mysql_real_escape_string(hName, hName);
    format(Query, sizeof(Query), "SELECT * FROM `users` WHERE `Username` = '%s'", hName);
    mysql_query(Query);
    mysql_store_result();
    return mysql_num_rows();
}

strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

