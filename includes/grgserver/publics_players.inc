public OnPlayerConnect(playerid)
{
	new query[256];
	new playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);
	format(query, sizeof(query), "SELECT * FROM `users` WHERE `Username` = '%s'", mySQLEscapeString(playerName));
	mysql_query(query);
	mysql_store_result();
 	if (strval(getMySQLField("UserID")))
	{
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Login", "Bitte gebe das Passwort von deinen Account ein.", "OK", "Abbrechen");
	}
	else
	{
		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Registrieren", "Du bist noch nicht registriert!\nBitte gebe ein neues Passwort für deinen Account ein.", "OK", "Abbrechen");
	}
	mysql_free_result();
	return true;
}

public OnPlayerDisconnect(playerid, reason)
{
	if (GetPVarInt(playerid, "UserID"))
	{
		savePlayer(playerid);
	}
	return true;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return true;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case DIALOG_LOGIN:
		{
			if (response)
			{
				if (strlen(inputtext))
				{
					new playerName[MAX_PLAYER_NAME];
					new query[256];
					GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);
					format(query, sizeof(query), "SELECT * FROM `users` WHERE `Username` = '%s'", mySQLEscapeString(playerName));
					mysql_query(query);
					mysql_store_result();
					if (!strcmp(MD5_Hash(inputtext, true), getMySQLField("Password"), true))
					{
						SetPVarInt(playerid, "UserID", strval(getMySQLField("UserID")));
					}
					else
					{
						ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Login", "Das angegebene Passwort ist falsch!\nBtte versuche es erneut.", "OK", "Abbrechen");
					}
					mysql_free_result();
					if (GetPVarInt(playerid, "UserID"))
					{
						loadPlayer(playerid);
						printf("Player logged in: %s (UserID: %d)", playerName, GetPVarInt(playerid, "UserID"));
						SendClientMessage(playerid, COLOR_INFO, "Du wurdest erfolgreich eingeloggt.");
						SpawnPlayer(playerid);
					}
				}
				else
				{
					ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Login", "Kein Passwort eingegeben!\nBitte versuche es erneut.", "OK", "Abbrechen");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_INFO, "Du kannst nun das Spiel beenden!");
				Kick(playerid);
			}
			return true;
		}
		case DIALOG_REGISTER:
		{
			if (response)
			{
				if (strlen(inputtext) >= REGISTER_MINPASSWORD && strlen(inputtext) <= REGISTER_MAXPASSWORD)
				{
					new query[256];
					new playerName[MAX_PLAYER_NAME];
					GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);
					format(query, sizeof(query), "INSERT INTO `users` (`Username`, `Password`) VALUES ('%s', '%s')", mySQLEscapeString(playerName), MD5_Hash(inputtext, true));
					mysql_query(query);
					SetPVarInt(playerid, "UserID", mysql_insert_id());
					printf("UserID: %d", GetPVarInt(playerid, "UserID"));
					SetPVarInt(playerid, "Level", REGISTER_LEVEL);
					SetPVarInt(playerid, "AdminLevel", REGISTER_ADMINLEVEL);
					print("PVar set");
					savePlayer(playerid);
					printf("Player registered: %s (UserID: %d)", playerName, GetPVarInt(playerid, "UserID"));
					SendClientMessage(playerid, COLOR_INFO, "Du wurdest erfolgreich registriert und bist nun eingeloggt.");
					SpawnPlayer(playerid);
				}
				else
				{
					new string[256];
					format(string, sizeof(string), "Bitte verwende ein Passwort mit einer Länge zwischen %d und %d Zeichen!", REGISTER_MINPASSWORD, REGISTER_MAXPASSWORD);
					ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Registrieren", string, "OK", "Abbrechen");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_INFO, "Du kannst nun das Spiel beenden!");
				Kick(playerid);
			}
			return true;
		}
	}

	return false;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	switch (success)
	{
		case COMMAND_ERROR:
			return true;// Command occured an error (Player not found, invalid ID, etc.) -> Nothing to do yet
		case COMMAND_OK:
			return true;// Command executed successfully -> Do nothing
		case COMMAND_TELEPORTED:
			SendClientMessage(playerid, COLOR_INFO, "Du wurdest teleportiert!");
		case COMMAND_ACCESS_DENIED:
		{
			SendClientMessage(playerid, COLOR_ERROR, "Du hast nicht die nötigen Rechte um diesen Befehl zu verwenden!");
			printf("%s tried to execute %s with admin level %d but has not the required permission!", getPlayerName(playerid), cmdtext, GetPVarInt(playerid, "AdminLevel"));
		}
		case COMMAND_NOT_FOUND:
			return false;
		default:
			printf("Unknown command return code from %s", cmdtext);
	}
	return true;
}