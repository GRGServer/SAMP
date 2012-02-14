public OnPlayerConnect(playerid)
{
	new query[256];
	if (IsPlayerNPC(playerid))
	{
		format(query, sizeof(query), "SELECT * FROM `npcs` WHERE `Name` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
		mysql_query(query);
		mysql_store_result();
		if (strval(GetMySQLField("StartOnConnect")))
		{
			new modelID;
			new playbackType;
			new vehicleID;
			modelID = strval(GetMySQLField("VehicleModelID"));
			if (modelID)
			{
				playbackType = PLAYER_RECORDING_TYPE_DRIVER;
				vehicleID = CreateVehicle(modelID, 0.0, 0.0, 0.0, 0.0, random(126), random(126), 1);
				PutPlayerInVehicle(playerid, vehicleID, 0);
				SetPVarInt(playerid, "VehicleID", vehicleID);
			}
			else
			{
				playbackType = PLAYER_RECORDING_TYPE_ONFOOT;
			}
			StartNPCPlayback(playerid, GetMySQLField("Recording"), playbackType, strval(GetMySQLField("AutoRepeat")));
		}
		mysql_free_result();
	}
	else
	{
		format(query, sizeof(query), "SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
		mysql_query(query);
		mysql_store_result();
		if (strval(GetMySQLField("UserID")))
		{
			ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Login", "Bitte gebe das Passwort von deinen Account ein.", "OK", "Abbrechen");
		}
		else
		{
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Registrieren", "Du bist noch nicht registriert!\nBitte gebe ein neues Passwort für deinen Account ein.", "OK", "Abbrechen");
		}
		mysql_free_result();
		new string[256];
		SendClientMessage(playerid, COLOR_SYSTEM, "Willkommen auf GRG Server!");
		format(string, sizeof(string), "Auf diesem Server läuft aktuell Revision %d unserer Gamemode.", COMPILER_SVN_REVISION);
		SendClientMessage(playerid, COLOR_SYSTEM, string);
		format(string, sizeof(string), "%s hat den Server betreten", GetPlayerNameEx(playerid));
		SendClientMessageToAllExcept(playerid, COLOR_JOINLEAVE, string);
		IRC_Say(ircBot, IRC_CHANNEL, string);
		textDrawSpeedoColumn2[playerid] = TextDrawCreate(580, 400, "_");
		TextDrawAlignment(textDrawSpeedoColumn2[playerid], 1);
		TextDrawLetterSize(textDrawSpeedoColumn2[playerid], 0.3, 0.9);
		TextDrawFont(textDrawSpeedoColumn2[playerid], 1);
		TextDrawSetShadow(textDrawSpeedoColumn2[playerid], 2);
		TextDrawTextSize(textDrawSpeedoColumn2[playerid], 635, 475);
		TextDrawShowForPlayer(playerid, textDrawClock);
		TextDrawShowForPlayer(playerid, textDrawBottomBanner);
	}
	return true;
}

public OnPlayerPickUpPickup(playerid,pickupid)
{
	switch (pickups[pickupid][pickups_type])
	{
		case PICKUPTYPE_HOUSE:
		{
			new string[256];
			new Float:price = floatstr(GetMySQLValue("house", "Price", "ID", val2str(houses_saveID)));
			format(string,sizeof(string),"Möchtest du dieses Haus für $%d kaufen?", price);
			ShowPlayerDialog(playerid,DIALOG_HOUSE,DIALOG_STYLE_MSGBOX,"Haus Kaufen",string,"Kaufen", "Abbrechen");
		}
		case PICKUPTYPE_BANK:
		{
			SendClientMessage(playerid, COLOR_INFO, "Du stehst in einem Bank Pickup");
		}
		case PICKUPTYPE_GASSTATION:
		{
			new vehicleID = GetPlayerVehicleID(playerid);
			new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][vehicleModels_maxFuel], vehicles[vehicleID][vehicles_currentFuel]);
			if (maximum > 0)
			{
				new string[256];
				format(string, sizeof(string), "Wie viel möchtest du tanken (0 - %s)?", FormatNumber(maximum, 2, 0, '.'));
				ShowPlayerDialog(playerid, DIALOG_REFUEL, DIALOG_STYLE_INPUT, "Tanken", string, "Tanken", "Abbrechen");
			}
			else
			{
				SendClientMessage(playerid, COLOR_ERROR, "Der Tank ist bereits voll!");
			}
		}
	}
	return true;
}

public OnPlayerDisconnect(playerid, reason)
{
	if (!IsPlayerNPC(playerid))
	{
		SavePlayer(playerid);
		new string[256];
		format(string, sizeof(string), "%s hat den Server verlassen", GetPlayerNameEx(playerid));
		SendClientMessageToAll(COLOR_JOINLEAVE, string);
		IRC_Say(ircBot, IRC_CHANNEL, string);
		TextDrawHideForPlayer(playerid, textDrawSpeedoColumn1);
		TextDrawHideForPlayer(playerid, textDrawClock);
		TextDrawHideForPlayer(playerid, textDrawBottomBanner);
		TextDrawDestroy(textDrawSpeedoColumn2[playerid]);
	}
	return true;
}

public OnPlayerRequestClass(playerid, classid)
{
	new previousClassID = GetPVarInt(playerid, "PreviousClassID");
	new direction;
	switch (classid)
	{
		case 0:
		{
			switch (previousClassID)
			{
				case 1:
					direction--;
				case 2:
					direction++;
			}
		}
		case 1:
		{
			switch (previousClassID)
			{
				case 2:
					direction--;
				case 0:
					direction++;
			}
		}
		case 2:
		{
			switch (previousClassID)
			{
				case 0:
					direction--;
				case 1:
					direction++;
			}
		}
	}
	SetPVarInt(playerid, "PreviousClassID", classid);
	new skinID = GetPVarInt(playerid, "Skin");
	switch (direction)
	{
		case -1:
		{
			do
			{
				skinID--;
				if (skinID < 0)
				{
					skinID = 298;
				}
			}
			while (!IsValidSkin(skinID));
		}
		case 1:
		{
			do
			{
				skinID++;
				if (skinID > 298)
				{
					skinID = 0;
				}
			}
			while (!IsValidSkin(skinID));
		}
	}
	SetPVarInt(playerid, "Skin", skinID);
	SetPlayerSkin(playerid, skinID);
	new string[256];
	format(string, sizeof(string), "Player/ClassID/Direction/SkinID: %s/%d/%d/%d", GetPlayerNameEx(playerid), classid, direction, skinID);
	SendClientMessage(playerid, COLOR_SYSTEM, string);
	SetPlayerPos(playerid, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ);
	SetPlayerFacingAngle(playerid, SPAWN_ANGLE);
	SetPlayerCameraPos(playerid, SPAWN_CAMERAPOSX, SPAWN_CAMERAPOSY, SPAWN_CAMERAPOSZ);
	SetPlayerCameraLookAt(playerid, SPAWN_POSX, SPAWN_POSY, SPAWN_POSZ);
	return true;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case DIALOG_RADIO:
		{
			new VID = GetPlayerVehicleID(playerid);
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						KillTimer(timer_radio);
						entftextdraw(playerid);
						closed[playerid] = 1;
						channels[VID] = 1;
						StopAudioStreamForPlayer(playerid);
						PlayAudioStreamForPlayer(playerid, "http://gffstream.ic.llnwd.net/stream/gffstream_stream_wdr_einslive_a");//1LIVE
						TextDrawShowForPlayer(playerid,LIVE);
						timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					}
					case 1:
					{
						ShowPlayerDialog(playerid,DIALOG_RADIO1,DIALOG_STYLE_LIST,"Wähle einen Sender","YouFM Live\nYouFM Rock\nYouFM Club\nYouFM Black\n{FF0000}<- Zurück","Auswählen", "Abbrechen");
					}
					case 2:
					{
						KillTimer(timer_radio);
						entftextdraw(playerid);
						closed[playerid] = 1;
						channels[VID] = 6;
						StopAudioStreamForPlayer(playerid);
						TextDrawShowForPlayer(playerid,RTL);
						timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
						PlayAudioStreamForPlayer(playerid, "http://mp3.89.0rtl.de/listen.pls"); // 89.0 RTL
					}
					case 3:
					{
						channels[VID] = 7;
						KillTimer(timer_radio);
						entftextdraw(playerid);
						closed[playerid] = 1;
						StopAudioStreamForPlayer(playerid);
						PlayAudioStreamForPlayer(playerid, "http://streams.planetradio.de/planetradio/mp3/hqlivestream.m3u"); // Planet Radio
						TextDrawShowForPlayer(playerid,radioplanet);
						timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					}
					case 4:
					{
						KillTimer(timer_radio);
						entftextdraw(playerid);
						closed[playerid] = 1;
						channels[VID] = 8;
						StopAudioStreamForPlayer(playerid);
						TextDrawShowForPlayer(playerid,technobase);
						timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
						PlayAudioStreamForPlayer(playerid, "http://listen.technobase.fm/dsl.pls"); // Technobase
					}
					case 5:
					{
						channels[VID] = 0;
						KillTimer(timer_radio);
						entftextdraw(playerid);
						TextDrawShowForPlayer(playerid,RADIOAUS);
						StopAudioStreamForPlayer(playerid);
						timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					}
				}
			}
		}
		case DIALOG_RADIO1:
		{
			new VID = GetPlayerVehicleID(playerid);
			switch(listitem)
			{
				case 0:
				{
					KillTimer(timer_radio);
					entftextdraw(playerid);
					closed[playerid] = 1;
					channels[VID] = 2;
					StopAudioStreamForPlayer(playerid);
					TextDrawShowForPlayer(playerid,YOUFM);
					timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_2.m3u");//YOU FM LIVE
				}
				case 1:
				{
					KillTimer(timer_radio);
					entftextdraw(playerid);
					closed[playerid]=1;
					channels[VID]=3;
					StopAudioStreamForPlayer(playerid);
					TextDrawShowForPlayer(playerid,YOUFM2);
					timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_rock.m3u"); // YOU FM ROCK
				}
				case 2:
				{
					KillTimer(timer_radio);
					entftextdraw(playerid);
					closed[playerid]=1;
					channels[VID]=4;
					StopAudioStreamForPlayer(playerid);
					TextDrawShowForPlayer(playerid,YOUFM3);
					timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_club.m3u"); // YOU FM CLUB
				}
				case 3:
				{
					KillTimer(timer_radio);
					entftextdraw(playerid);
					closed[playerid]=1;
					channels[VID]=5;
					StopAudioStreamForPlayer(playerid);
					TextDrawShowForPlayer(playerid,YOUFM4);
					timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
					PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_black.m3u"); // YOU FM BLACK
				}
				case 4:
				{
					ShowPlayerDialog(playerid,DIALOG_RADIO,DIALOG_STYLE_LIST,"Wähle einen Sender","1LIVE\nYouFM ->\n89.0 RTL\nPlanet Radio\nTechnoBase FM\n{FF0000}Radio aus","Auswählen", "Abbrechen");
				}
			}
		}
		case DIALOG_HOUSE:
		{
			if (response)
			{
				for (new pickupID; pickupID < MAX_PICKUPS; pickupID++)
				{
					new ownerUserID = strval(GetMySQLValue("house", "OwnerUserID", "ID", val2str(houses[playerid][houses_saveID])));
					new Float:price = floatstr(GetMySQLValue("house", "Price", "ID", val2str(houses_saveID)));
					if(ownerUserID == 0)
					{
						SetPlayerMoney(playerid, floatsub(GetPVarFloat(playerid, "Money"), price));
						SetMySQLValue("house", "ownerUserID", val2str(GetPVarInt(playerid, "UserID")), "ID", val2str(houses_saveID));
						SavePlayer(playerid);
						pickups[pickupID][pickups_type] = PICKUP_HOUSEBOUGHT;
					}
					else
					{
						SendClientMessage(playerid,COLOR_ERROR,"Dieses Haus ist bereits Verkauft!");
					}
				}
			}
			else
			{
				SendClientMessage(playerid,COLOR_INFO,"Vorgang abgebrochen!");
			}
		}
		case DIALOG_BUYVEHICLE:
		{
			if (response)
			{
				new string[256];
				new saveID = vehicles[GetPlayerVehicleID(playerid)][vehicles_saveID];
				new Float:price = floatstr(GetMySQLValue("savedvehicles", "Price", "ID", val2str(saveID)));
				if (price <= GetPVarFloat(playerid, "Money"))
				{
					SetPlayerMoney(playerid, floatsub(GetPVarFloat(playerid, "Money"), price));
					SetMySQLValue("savedvehicles", "ownerUserID", val2str(GetPVarInt(playerid, "UserID")), "ID", val2str(saveID));
					SavePlayer(playerid);
				}
				else
				{
					format(string,sizeof(string), "Du benötigst $%f für dieses Fahrzeug! Leider hast du nur $%f.", price, GetPVarFloat(playerid, "Money"));
					SendClientMessage(playerid, COLOR_ERROR, string);
					RemovePlayerFromVehicle(playerid);
				}
			}
			else
			{
				RemovePlayerFromVehicle(playerid);
			}
		}
		case DIALOG_LOGIN:
		{
			if (response)
			{
				if (strlen(inputtext))
				{
					new playerName[MAX_PLAYER_NAME];
					new query[256];
					GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);
					format(query, sizeof(query), "SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(playerName));
					mysql_query(query);
					mysql_store_result();
					if (!strcmp(MD5(inputtext), GetMySQLField("Password"), true))
					{
						SetPVarInt(playerid, "UserID", strval(GetMySQLField("UserID")));
					}
					else
					{
						ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Login", "Das angegebene Passwort ist falsch!\nBtte versuche es erneut.", "OK", "Abbrechen");
					}
					mysql_free_result();
					if (GetPVarInt(playerid, "UserID"))
					{
						format(query, sizeof(query), "UPDATE `users` SET `LoginTime` = NOW() WHERE `UserID` = '%d'", GetPVarInt(playerid, "UserID"));
						mysql_query(query);
						printf("Player logged in: %s (UserID: %d)", playerName, GetPVarInt(playerid, "UserID"));
						LoadPlayer(playerid);
						SetSpawnPlayer(playerid);
						// SetTimerEx("timer_spawnPlayer", 10, false, "i", playerid);
						SendClientMessage(playerid, COLOR_INFO, "Du wurdest erfolgreich eingeloggt.");
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
		case DIALOG_REFUEL:
		{
			if (response && strlen(inputtext))
			{
				new Float:amount = floatstr(inputtext);
				new vehicleID = GetPlayerVehicleID(playerid);
				new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][vehicleModels_maxFuel], vehicles[vehicleID][vehicles_currentFuel]);
				if (amount > maximum)
				{
					amount = maximum;
				}
				TogglePlayerControllable(playerid, false);
				SetVehicleEngineState(vehicleID, false);
				GameTextForPlayer(playerid, "Dein Fahrzeug wird getankt. Bitte warten...", 3000, 4);
				timer_refuelVehicle(playerid, amount);
			}
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
					format(query, sizeof(query), "INSERT INTO `users` (`Username`, `Password`, `RegisterTime`) VALUES ('%s', '%s', NOW())", MySQLEscapeString(playerName), MD5(inputtext));
					mysql_query(query);
					SetPVarInt(playerid, "UserID", mysql_insert_id());
					SetPVarInt(playerid, "Level", REGISTER_LEVEL);
					SetPVarInt(playerid, "AdminLevel", REGISTER_ADMINLEVEL);
					SavePlayer(playerid);
					SetPVarInt(playerid, "AllowSkinSelection", true);
					printf("Player registered: %s (UserID: %d)", playerName, GetPVarInt(playerid, "UserID"));
					SendClientMessage(playerid, COLOR_INFO, "Du wurdest erfolgreich registriert und bist nun eingeloggt.");
					SendClientMessage(playerid, COLOR_INFO, "Bitte wähle deinen Spieler aus.");
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

forward SetSpawnPlayer(playerid);
public SetSpawnPlayer(playerid)
{
	new query[256];
	format(query, sizeof(query), "SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
	mysql_query(query);
	mysql_store_result();
	if (strval(GetMySQLField("UserID")))
	{
		SetPlayerPos(playerid, floatstr(GetUserDBValue(playerid, "PosX")), floatstr(GetUserDBValue(playerid, "PosY")), floatstr(GetUserDBValue(playerid, "PosZ")));
		SendClientMessage(playerid,COLOR_INFO,"Du bist nun an deinem Letzten logout Gespawnt!");
	}
	return true;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	switch (success)
	{
		case COMMAND_ERROR:
			SendClientMessage(playerid, COLOR_ERROR, "Fehler bei der Befehlsausführung!");
		case COMMAND_USAGE:
			return true;// Command usage message displayed -> Nothing to do yet
		case COMMAND_OK:
			return true;// Command executed successfully -> Do nothing
		case COMMAND_TELEPORTED:
			SendClientMessage(playerid, COLOR_INFO, "Du wurdest teleportiert!");
		case COMMAND_NPC_ONLY:
			SendClientMessage(playerid, COLOR_ERROR, "Diese Befehl ist nur für NPCs verfügbar!");
		case COMMAND_NOT_IN_VEHICLE:
			SendClientMessage(playerid, COLOR_ERROR, "Du bist nicht in einem Fahrzeug!");
		case COMMAND_ACCESS_DENIED:
		{
			SendClientMessage(playerid, COLOR_ERROR, "Du hast nicht die nötigen Rechte um diesen Befehl zu verwenden!");
			printf("%s tried to execute %s with admin level %d but has not the required permission!", GetPlayerNameEx(playerid), cmdtext, GetPVarInt(playerid, "AdminLevel"));
		}
		case COMMAND_NOT_FOUND:
			return false;
		default:
			printf("Unknown command return code from %s", cmdtext);
	}
	return true;
}

public OnPlayerText(playerid, text[])
{
	new string[256];
	format(string, sizeof(string), "[%s] %s", GetPlayerNameEx(playerid), text);
	IRC_Say(ircBot, IRC_CHANNEL, string);
	SendClientMessageToAllExcept(playerid, COLOR_CHAT, string);
	SendClientMessage(playerid, COLOR_CHATOWN, string);
	WriteChatToDatabase(playerid, text);
	return false;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (!ispassenger && !IsPlayerNPC(playerid))
	{
		SetVehicleEngineState(vehicleid, false);
	}
	if (!ispassenger)
	{
		if (vehicles[vehicleid][vehicles_saveID])
		{
			new string[256];
			new ownerUserID = strval(GetMySQLValue("savedvehicles", "OwnerUserID", "ID", val2str(vehicles[vehicleid][vehicles_saveID])));
			if (ownerUserID == GetPVarInt(playerid, "UserID"))
			{
				return true;
			}
			if (ownerUserID)
			{
				SendClientMessage(playerid, COLOR_ERROR, "Dieses Fahrzeug besitzt bereits ein anderer Spieler");
				RemovePlayerFromVehicle(playerid);
			}
			else
			{
				format(string,sizeof(string), "Möchtest du dieses Fahrzeug Kaufen?\nDies kostet $%s", GetMySQLValue("savedvehicles", "Price", "ID", val2str(vehicles[vehicleid][vehicles_saveID])));
				ShowPlayerDialog(playerid, DIALOG_BUYVEHICLE,DIALOG_STYLE_MSGBOX, "Fahrzeug Kaufen", string, "Ja", "Nein");
			}
		}
	}
	switch(channels[vehicleid])
	{
		case 0:
		{
			KillTimer(timer_radio);
			entftextdraw(playerid);
			TextDrawShowForPlayer(playerid,RADIOAUS);
			timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
			StopAudioStreamForPlayer(playerid);
			SendClientMessage(playerid,COLOR_INFO,"Tippe /radio um das Radio einzuschalten!");
		}
		case 1:
		{
			KillTimer(timer_radio);
			entftextdraw(playerid);
			closed[playerid] = 1;
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, "http://gffstream.ic.llnwd.net/stream/gffstream_stream_wdr_einslive_a");//1LIVE
			TextDrawShowForPlayer(playerid,LIVE);
			timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 2:
		{
			KillTimer(timer_radio);
			entftextdraw(playerid);
			closed[playerid] = 1;
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_2.m3u");//YOU FM LIVE
			TextDrawShowForPlayer(playerid,YOUFM);
			timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 3:
		{
			KillTimer(timer_radio);
			entftextdraw(playerid);
			closed[playerid] = 1;
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_rock.m3u"); // YOU FM ROCK
			TextDrawShowForPlayer(playerid,YOUFM2);
			timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 4:
		{
			KillTimer(timer_radio);
			entftextdraw(playerid);
			closed[playerid] = 1;
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_club.m3u"); // YOU FM CLUB
			TextDrawShowForPlayer(playerid,YOUFM3);
			timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 5:
		{
			KillTimer(timer_radio);
			entftextdraw(playerid);
			closed[playerid] = 1;
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_black.m3u"); // YOU FM BLACK
			TextDrawShowForPlayer(playerid,YOUFM4);
			timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 6:
		{
			KillTimer(timer_radio);
			entftextdraw(playerid);
			closed[playerid] = 1;
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, "http://mp3.89.0rtl.de/listen.pls"); // 89.0 RTL
			TextDrawShowForPlayer(playerid,RTL);
			timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 7:
		{
			KillTimer(timer_radio);
			entftextdraw(playerid);
			closed[playerid] = 1;
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, "http://streams.planetradio.de/planetradio/mp3/hqlivestream.m3u"); // Planet Radio
			TextDrawShowForPlayer(playerid,radioplanet);
			timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
		case 8:
		{
			KillTimer(timer_radio);
			entftextdraw(playerid);
			closed[playerid] = 1;
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, "http://listen.technobase.fm/dsl.pls"); // TechnoBase
			TextDrawShowForPlayer(playerid,technobase);
			timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
		}
	}
	return true;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsPlayerNPC(playerid))
	{
		SetVehicleEngineState(vehicleid, false);
	}
	SaveVehicle(vehicleid, GetPlayerInterior(playerid));
	StopAudioStreamForPlayer(playerid);
	return true;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	vehicles[vehicleid][vehicles_paintjobID] = paintjobid;
	return true;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	vehicles[vehicleid][vehicles_color1] = color1;
	vehicles[vehicleid][vehicles_color2] = color2;
	return true;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new VID = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(channels[VID] != 0)
		{
			if(PRESSED(KEY_ANALOG_UP))
			{
				if(closed[playerid] != 1)
				{
					switch(channels[VID])
					{
						case 1:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID]=8;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,technobase);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://listen.technobase.fm/dsl.pls"); // Technobase
						}
						case 2:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID]=1;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,LIVE);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://gffstream.ic.llnwd.net/stream/gffstream_stream_wdr_einslive_a");//1LIVE
						}
						case 3:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 2;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,YOUFM);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_2.m3u");//YOU FM LIVE
						}
						case 4:
						{
			 				KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 2;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,YOUFM2);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_rock.m3u"); // YOU FM ROCK
						}
						case 5:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 2;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,YOUFM3);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_club.m3u"); // YOU FM CLUB
						}
						case 6:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 2;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,YOUFM4);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_black.m3u"); // YOU FM BLACK
						}
						case 7:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 2;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,RTL);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://mp3.89.0rtl.de/listen.pls"); // 89.0 RTL
						}
						case 8:
						{
							channels[VID] = 2;
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,radioplanet);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://streams.planetradio.de/planetradio/mp3/hqlivestream.m3u"); // Planet Radio
						}
					}
				}
				return 1;
			}
			if(PRESSED(KEY_ANALOG_DOWN))
			{
				if(closed[playerid] != 1)
				{
					switch(channels[VID])
					{
						case 1:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 2;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,YOUFM);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_2.m3u");//YOU FM LIVE
						}
						case 2:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 2;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,YOUFM2);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_rock.m3u"); // YOU FM ROCK
						}
						case 3:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 2;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,YOUFM3);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_club.m3u"); // YOU FM CLUB
						}
						case 4:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 2;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,YOUFM4);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://metafiles.gl-systemhaus.de/hr/youfm_black.m3u"); // YOU FM BLACK
						}
						case 5:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 2;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,RTL);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://mp3.89.0rtl.de/listen.pls"); // 89.0 RTL
						}
						case 6:
						{
							channels[VID] = 2;
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							StopAudioStreamForPlayer(playerid);
							PlayAudioStreamForPlayer(playerid, "http://streams.planetradio.de/planetradio/mp3/hqlivestream.m3u"); // Planet Radio
							TextDrawShowForPlayer(playerid,radioplanet);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
						}
						case 7:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 2;
							StopAudioStreamForPlayer(playerid);
							TextDrawShowForPlayer(playerid,technobase);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
							PlayAudioStreamForPlayer(playerid, "http://listen.technobase.fm/dsl.pls"); // Technobase
						}
						case 8:
						{
							KillTimer(timer_radio);
							entftextdraw(playerid);
							closed[playerid] = 1;
							channels[VID] = 1;
							StopAudioStreamForPlayer(playerid);
							PlayAudioStreamForPlayer(playerid, "http://gffstream.ic.llnwd.net/stream/gffstream_stream_wdr_einslive_a");//1LIVE
							TextDrawShowForPlayer(playerid,LIVE);
							timer_radio = SetTimerEx("entftextdraw", 2500, false, "i",playerid);
						}
					}
				}
			}
		}
	}
	return 1;
}
forward entftextdraw(playerid);
public entftextdraw(playerid)
{
	TextDrawHideForPlayer(playerid,radioplanet);
	TextDrawHideForPlayer(playerid,LIVE);
	TextDrawHideForPlayer(playerid,YOUFM);
	TextDrawHideForPlayer(playerid,YOUFM2);
	TextDrawHideForPlayer(playerid,YOUFM3);
	TextDrawHideForPlayer(playerid,YOUFM4);
	TextDrawHideForPlayer(playerid,RTL);
	TextDrawHideForPlayer(playerid,RADIOAUS);
	TextDrawHideForPlayer(playerid,technobase);
 	closed[playerid] = 0;
}