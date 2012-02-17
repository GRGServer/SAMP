public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case DIALOG_SHOWINTERIOR:
		{
			if(response)
			{
				if(!strcmp(inputtext, "Zurück", true))
				{
					ShowDialog(playerid, DIALOG_SHOWINTERIOR, 0);
				}
				else
				{
					if(!strcmp(inputtext, "Weiter", true))
					{
						ShowDialog(playerid, DIALOG_SHOWINTERIOR, 75);
					}
					else
					{
						mysql_query("SELECT * FROM `interiors`");
						mysql_store_result();
						new Float:PosX = floatstr(GetMySQLField("PosX"));
						new Float:PosY = floatstr(GetMySQLField("PosX"));
						new Float:PosZ = floatstr(GetMySQLField("PosX"));
						new Float:Angle = floatstr(GetMySQLField("Angle"));
						new Interior = strval(GetMySQLField("Interior"));
						SetPlayerPos(playerid, PosX, PosY, PosZ);
						SetPlayerFacingAngle(playerid, Angle);
						SetPlayerInterior(playerid, Interior);
					}
				}
			}
		}
		case DIALOG_ADDHOUSE:
		{
			if (response)
			{
				if (!strcmp(inputtext, "Zurück", true))
				{
					ShowDialog(playerid, DIALOG_ADDHOUSE, 0);
				}
				else
				{
					if (!strcmp(inputtext, "Weiter", true))
					{
						ShowDialog(playerid, DIALOG_ADDHOUSE, 75);
					}
					else
					{
						new string[256];
						new query[256];
						new name[256];
						new Float:price = GetPVarFloat(playerid, "AddHouse_Price");
						new Float:posX;
						new Float:posY;
						new Float:posZ;
						GetPVarString(playerid, "AddHouse_Name", name, sizeof(name));
						GetPlayerPos(playerid, posX, posY, posZ);
						new pickupID = AddPickup("HOUSE", posX, posY, posZ, true);
						if (pickupID > 0)
						{
							format(query, sizeof(query), "INSERT INTO `houses` (`PickupID`, `InteriorID`, `Name`, `Price`) VALUES ('%d', '%s', '%s', '%f')", pickupID, GetMySQLValue("interiors", "ID", "Name", inputtext), name, price);
							mysql_query(query);
							format(string, sizeof(string), "Das Haus %s (Preis: %s) wurde mit dem Ziel %s verknüpft und unter der ID %d gespeichert.", name, FormatNumber(price, 2, '.', ','), inputtext, mysql_insert_id());
							SendClientMessage(playerid, COLOR_INFO, string);
						}
						else
						{
							SendClientMessage(playerid, COLOR_ERROR, "Fehler beim Erstellen des Pickups!");
						}
					}
				}
			}
			DeletePVar(playerid, "AddHouse_Name");
			DeletePVar(playerid, "AddHouse_Price");
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
		/* TODO: Write working code
		case DIALOG_HOUSE:
		{
			if (response)
			{
				new saveID = houses[playerid][houses_saveID];
				new Float:price = floatstr(GetMySQLValue("house", "Price", "ID", val2str(houses_saveID)));
				new ownerUserID = strval(GetMySQLValue("house", "OwnerUserID", "ID", val2str(houses[playerid][houses_saveID])));
				if(price <= GetPVarFloat(playerid, "Money"))
				{
					for (new pickupID; pickupID < MAX_PICKUPS; pickupID++)
					{
						if(ownerUserID == 0)
						{
							SetPlayerMoney(playerid, floatsub(GetPVarFloat(playerid, "Money"), price));
							SetMySQLValue("house", "ownerUserID", val2str(GetPVarInt(playerid, "UserID")), "ID", val2str(saveID));
							SavePlayer(playerid);
							pickups[pickupID][pickups_type] = PICKUP_HOUSEBOUGHT;
						}
						else
						{
							SendClientMessage(playerid,COLOR_ERROR,"Dieses Haus ist bereits Verkauft!");
						}
					}
				}
			}
			else
			{
				SendClientMessage(playerid,COLOR_INFO,"Vorgang abgebrochen!");
			}
		}*/
		case DIALOG_HOUSEOPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:// Enter
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Haus betreten");
						mysql_query("SELECT * FROM `interiors`");
						mysql_store_result();
						while (FetchMySQLRow())
						{
							new Float:PosX = floatstr(GetMySQLField("PosX"));
							new Float:PosY = floatstr(GetMySQLField("PosY"));
							new Float:PosZ = floatstr(GetMySQLField("PosZ"));
							new interior = strval(GetMySQLField("Interior"));
							SetPlayerPos(playerid,PosX,PosY,PosZ);
							SetPlayerInterior(playerid, interior);
						}
						mysql_query("SELECT * FROM `houses`");
						mysql_store_result();
						while (FetchMySQLRow())
						{
							new houseID = strval(GetMySQLField("ID"));
							SetPlayerVirtualWorld(playerid, houseID);
						}
					}
					case 1:// Sell
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Haus verkaufen");
					}
					default:
					{
						SendClientMessage(playerid, COLOR_ERROR, "Ungültige Auswahl!");
					}
				}
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
						SendClientMessage(playerid, COLOR_ERROR, "Das angegebene Passwort ist falsch! Btte versuche es erneut.");
						ShowDialog(playerid, DIALOG_LOGIN);
					}
					mysql_free_result();
					if (GetPVarInt(playerid, "UserID"))
					{
						format(query, sizeof(query), "UPDATE `users` SET `LoginTime` = NOW() WHERE `UserID` = '%d'", GetPVarInt(playerid, "UserID"));
						mysql_query(query);
						printf("Player logged in: %s (UserID: %d)", playerName, GetPVarInt(playerid, "UserID"));
						LoadPlayer(playerid);
						SetPVarInt(playerid, "SpawnAfterLogin", true);
						SendClientMessage(playerid, COLOR_INFO, "Du wurdest erfolgreich eingeloggt.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_ERROR, "Kein Passwort eingegeben! Bitte versuche es erneut.");
					ShowDialog(playerid, DIALOG_LOGIN);
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_INFO, "Du kannst nun das Spiel beenden!");
				Kick(playerid);
			}
			return true;
		}
		case DIALOG_ORDERVEHICLE:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
					}
					case 1:
					{
					}
					case 2:
					{
					}
					case 3:
					{
					}
					case 4:
					{
					}
					case 5:
					{
					}
					case 6:
					{
					}
					case 7:
					{
					}
				}
			}
			else
			{
				SendClientMessage(playerid,COLOR_INFO,"Du hast den vorgang abgebrochen!");
			}
		}
		case DIALOG_RADIO:
		{
			if (response)
			{
				PlayRadioStation(playerid, strval(GetMySQLValue("radiostations", "ID", "Name", inputtext)));
			}
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
		case DIALOG_REGISTER_STEP1:
		{
			if (response)
			{
				if (strlen(inputtext) >= REGISTER_MINPASSWORD && strlen(inputtext) <= REGISTER_MAXPASSWORD)
				{
					SetPVarString(playerid, "RegisterPassword", inputtext);
					ShowDialog(playerid, DIALOG_REGISTER_STEP2);
				}
				else
				{
					new string[256];
					format(string, sizeof(string), "Bitte verwende ein Passwort mit einer Länge zwischen %d und %d Zeichen!", REGISTER_MINPASSWORD, REGISTER_MAXPASSWORD);
					SendClientMessage(playerid, COLOR_ERROR, string);
					ShowDialog(playerid, DIALOG_REGISTER_STEP1);
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_INFO, "Du kannst nun das Spiel beenden!");
				Kick(playerid);
			}
		}
		case DIALOG_REGISTER_STEP2:
		{
			if (response)
			{
				if (!strcmp(inputtext, GetPVarStringEx(playerid, "RegisterPassword")))
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
					SendClientMessage(playerid, COLOR_ERROR, "Die eingegebenen Passwörter stimmen nicht überein! Bitte versuche es erneut.");
					ShowDialog(playerid, DIALOG_REGISTER_STEP1);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_REGISTER_STEP1);
			}
			return true;
		}
	}

	return false;
}