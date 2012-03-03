public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case DIALOG_ACCEPT:
		{
			if (response)
			{
				new missionID;
				new text[100];
				sscanf(inputtext, "p:ds", missionID, text);
				if (strval(GetMySQLValue("missions", "AcceptUserID", "ID", val2str(missionID))))
				{
					SendClientMessage(playerid, COLOR_ERROR, "Dieser Auftrag wurde bereits von einem anderen Spieler angenommen!");
				}
				else
				{
					SetMySQLValue("missions", "AcceptUserID", val2str(GetUserID(playerid)), "ID", val2str(missionID));
					SendClientMessage(playerid, COLOR_INFO, "Du hast den Auftrag angenommen");
					FormatNew:string[90]("%s hat deinen Auftrag (Auftragsnummer: %d) angenommen", GetPlayerNameEx(playerid), missionID);
					SendClientMessage(strval(GetMySQLValue("missions", "CreatorUserID", "ID", val2str(missionID))), COLOR_INFO, string);
				}
			}
		}
		/*case DIALOG_ADDHOTELROOM:
		{
			if (response)
			{
				if(!strcmp(inputtext, "Zurück", true))
				{
					ShowDialog(playerid, DIALOG_ADDHOTEL, 0);
				}
				else
				{
					if(!strcmp(inputtext, "Weiter", true))
					{
						ShowDialog(playerid, DIALOG_ADDHOTEL, 75);
					}
					else
					{
						new name[128];
						new hotel[128];
						new Float: PosX;
						new Float: PosY;
						new Float: PosZ;
						GetPvarString(playerid, "AddHotel_Name", name, sizeof(name));
						GetPlayerPos(playerid, PosX, PosY, PosZ);
						new pickupID = AddPickup(-1, "HOTELROOM", PosX, PosY, PosZ, true);
						if(pickupID > 0)
						{
							MySQLQuery("INSERT INTO `buildings` (`PickupID`, `InteriorID`, `Name`, `HotelOwner`) VALUES ('%d', '%s', '%s', '%s')", pickupID, GetMySQLValue("interior", "ID", "Name", inputtext), name, hotel);
							FormatNew:string[256]("Das Hotel Zimmer %s (Hotel: %s) wurde mit dem Ziel %s verknüpft und unter der ID %d gespeichert.", name, hotel, inputtext, mysql_insert_id());
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
			DeletePVar(playerid, "AddHouse_Hotel");
		}*/
		case DIALOG_ADDBUILDING_NAME:
		{
			if (response)
			{
				print("Trying to add pickup");
				new Float:posX;
				new Float:posY;
				new Float:posZ;
				new buildingID;
				new pickupID;
				GetPlayerPos(playerid, posX, posY, posZ);
				printf("Type: %s", GetPVarStringEx(playerid, "AddBuilding_Type"));
				pickupID = AddPickup(-1, GetPVarStringEx(playerid, "AddBuilding_Type"), posX, posY, posZ, true);
				printf("Added pickup: %d", pickupID);
				if (pickupID > 0)
				{
					printf("Got positive PickupID: %d", pickupID);
					MySQLQuery("INSERT INTO `buildings` (`PickupID`, `InteriorID`, `Name`, `Price`) VALUES ('%d', '%d', '%s', '%f')", pickupID, GetPVarInt(playerid, "AddBuilding_InteriorID"), MySQLEscapeString(inputtext), GetPVarFloat(playerid, "AddBuilding_Price"));
					buildingID = mysql_insert_id();
					printf("Added building %d", buildingID);
					SetPVarInt(playerid, "LastAddedBuilding", buildingID);
					printf("PVar LastAddedBuilding set to %d", buildingID);
					FormatNew:string[256]("Das Gebäude %s (Preis: $%s) wurde unter der ID %d gespeichert.", inputtext, FormatMoney(GetPVarFloat(playerid, "AddBuilding_Price")), buildingID);
					SendClientMessage(playerid, COLOR_INFO, string);
				}
				else
				{
					SendClientMessage(playerid, COLOR_ERROR, "Fehler beim Erstellen des Pickups!");
				}
			}
			else
			{
				DeletePVar(playerid, "AddBuilding_InteriorID");
				ShowInteriorDialog(playerid, INTERIORDIALOG_ADDBUILDING);
			}
		}
		case DIALOG_ADDBUILDING_TYPE:
		{
			if (response)
			{
				new type[10];
				switch (listitem)
				{
					case 0:
						Format:type("BANK");
					case 1:
						Format:type("HOTEL");
					case 2:
						Format:type("HOUSE");
					case 3:
						Format:type("POLICE");
				}
				SetPVarString(playerid, "AddBuilding_Type", type);
				ShowInteriorDialog(playerid, INTERIORDIALOG_ADDBUILDING);
			}
			else
			{
				DeletePVar(playerid, "AddBuilding_Price");
			}
		}
		case DIALOG_BUYVEHICLE:
		{
			if (response)
			{
				new saveID = vehicles[GetPlayerVehicleID(playerid)][VEHICLE_SAVEID];
				new Float:price = floatstr(GetMySQLValue("savedvehicles", "Price", "ID", val2str(saveID)));
				if (price <= GetPlayerMoneyEx(playerid))
				{
					GivePlayerMoneyEx(playerid, -price);
					SetMySQLValue("savedvehicles", "OwnerUserID", val2str(GetUserID(playerid)), "ID", val2str(saveID));
					SavePlayer(playerid);
				}
				else
				{
					FormatNew:string[80]("Du benötigst $%s für dieses Fahrzeug! Leider hast du nur $%s.", FormatMoney(price), FormatMoney(GetPlayerMoneyEx(playerid)));
					SendClientMessage(playerid, COLOR_ERROR, string);
					RemovePlayerFromVehicle(playerid);
				}
			}
			else
			{
				RemovePlayerFromVehicle(playerid);
			}
		}
		case DIALOG_BUYHOUSE:
		{
			if (response)
			{
				new buildingID = GetPVarInt(playerid, "DialogBuildingID");
				new Float:price = floatstr(GetMySQLValue("buildings", "Price", "ID", val2str(buildingID)));
				if (price <= GetPlayerMoneyEx(playerid))
				{
					GivePlayerMoneyEx(playerid, -price);
					SetMySQLValue("buildings", "OwnerUserID", val2str(GetUserID(playerid)), "ID", val2str(buildingID));
					ReloadPickup(strval(GetMySQLValue("buildings", "PickupID", "ID", val2str(buildingID))));
					SendClientMessage(playerid, COLOR_INFO, "Viel Spaß mit deinem neuen Haus");
				}
				else
				{
					FormatNew:string[80]("Du benötigst $%s für dieses Haus! Leider hast du nur $%s.", FormatMoney(price), FormatMoney(GetPlayerMoneyEx(playerid)));
					SendClientMessage(playerid, COLOR_ERROR, string);
				}
			}
		}
		case DIALOG_CHANGEPASSWORD_STEP1:
		{
			if (response)
			{
				if (!strcmp(GetUserDBValue(playerid, "Password"), MD5(inputtext), true))
				{
					ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP2);
				}
				else
				{
					SendClientMessage(playerid, COLOR_ERROR, "Das eingegebene Passwort ist falsch!");
					ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP1);
				}
			}
		}
		case DIALOG_CHANGEPASSWORD_STEP2:
		{
			if (response)
			{
				if (strlen(inputtext) >= REGISTER_PASSWORD_MIN && strlen(inputtext) <= REGISTER_PASSWORD_MAX)
				{
					SetPVarString(playerid, "ChangePassword", inputtext);
					ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP3);
				}
				else
				{
					FormatNew:string[80]("Bitte verwende ein Passwort mit einer Länge zwischen %d und %d Zeichen!", REGISTER_PASSWORD_MIN, REGISTER_PASSWORD_MAX);
					SendClientMessage(playerid, COLOR_ERROR, string);
					ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP2);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP1);
			}
		}
		case DIALOG_CHANGEPASSWORD_STEP3:
		{
			if (response)
			{
				if (!strcmp(GetPVarStringEx(playerid, "ChangePassword"), inputtext))
				{
					SetUserDBValue(playerid, "Password", MD5(inputtext));
					SendClientMessage(playerid, COLOR_INFO, "Dein Passwort wurde geändert");
				}
				else
				{
					SendClientMessage(playerid, COLOR_ERROR, "Die eingegebenen Passwörter stimmen nicht überein! Bitte versuche es erneut.");
					ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP3);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP2);
			}
		}
		case DIALOG_HOTEL_MAIN_AVAILABLE:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Buy
					{
						new buildingID = GetPVarInt(playerid, "DialogBuildingID");
						new Float:price = floatstr(GetMySQLValue("buildings", "Price", "ID", val2str(buildingID)));
						if (price <= GetPlayerMoneyEx(playerid))
						{
							GivePlayerMoneyEx(playerid, -price);
							SetMySQLValue("buildings", "OwnerUserID", val2str(GetUserID(playerid)), "ID", val2str(buildingID));
							ReloadPickup(strval(GetMySQLValue("buildings", "PickupID", "ID", val2str(buildingID))));
							SendClientMessage(playerid, COLOR_INFO, "Viel Spaß mit deinem neuen Hotel");
							ShowDialog(playerid, DIALOG_HOTEL_MAIN_OWNER);
						}
						else
						{
							FormatNew:string[80]("Du benötigst $%s für dieses Hotel! Leider hast du nur $%s.", FormatMoney(price), FormatMoney(GetPlayerMoneyEx(playerid)));
							SendClientMessage(playerid, COLOR_ERROR, string);
							ShowDialog(playerid, DIALOG_HOTEL_MAIN_AVAILABLE);
						}
					}
					case 1: // Rent
					{
						SendClientMessage(playerid, COLOR_SYSTEM,"Zimmer Mieten");
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_AVAILABLE);
					}
					case 2: // Enter
					{
						TeleportToBuilding(playerid, GetPVarInt(playerid, "DialogBuildingID"));
					}
				}
			}
			else
			{
				SetPlayerPos(playerid, GetPVarFloat(playerid, "Hotel_PreviousPosition_X"), GetPVarFloat(playerid, "Hotel_PreviousPosition_Y"), GetPVarFloat(playerid, "Hotel_PreviousPosition_Z"));
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
			}
		}
		case DIALOG_HOTEL_MAIN_BOUGHT:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Enter
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Eintrit in eigenes Hotel Zimmer");
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_BOUGHT);
					}
					case 1: // Rent
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Zimmer Mieten");
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_BOUGHT);
					}
					case 2: // Stop contract
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Kündigen");
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_BOUGHT);
					}
				}
			}
			else
			{
				SetPlayerPos(playerid, GetPVarFloat(playerid, "Hotel_PreviousPosition_X"), GetPVarFloat(playerid, "Hotel_PreviousPosition_Y"), GetPVarFloat(playerid, "Hotel_PreviousPosition_Z"));
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
			}
		}
		case DIALOG_HOTEL_MAIN_OWNER:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Enter
					{
						TeleportToBuilding(playerid, GetPVarInt(playerid, "DialogBuildingID"));
					}
					case 1: // Sell
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Hotel verkaufen");
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_OWNER);
					}
					case 2: // Incoming (Money)
					{
						SendClientMessage(playerid, COLOR_SYSTEM, "Einnahmen");
						ShowDialog(playerid, DIALOG_HOTEL_MAIN_OWNER);
					}
					case 3: // Room options
					{
						ShowDialog(playerid, DIALOG_HOTEL_ROOMS_LIST);
					}
				}
			}
			else
			{
				SetPlayerPos(playerid, GetPVarFloat(playerid, "Hotel_PreviousPosition_X"), GetPVarFloat(playerid, "Hotel_PreviousPosition_Y"), GetPVarFloat(playerid, "Hotel_PreviousPosition_Z"));
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
			}
		}
		case DIALOG_HOTEL_ROOMS_FREEOPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:// Set room rent price
					{
						ShowDialog(playerid, DIALOG_HOTEL_ROOMS_SETPRICE);
					}
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_HOTEL_ROOMS_LIST);
			}
		}
		case DIALOG_HOTEL_ROOMS_LIST:
		{
			if (response)
			{
				new playerName[MAX_PLAYER_NAME];
				new roomID;
				if (!sscanf(inputtext, "p:ds", roomID, playerName))
				{
					SetPVarInt(playerid, "Hotel_Options_RoomID", roomID);
					if (strval(GetMySQLValue("hotelrooms", "OwnerUserID", "RoomID", val2str(roomID))))
					{
						ShowDialog(playerid, DIALOG_HOTEL_ROOMS_OWNEDOPTIONS);
					}
					else
					{
						ShowDialog(playerid, DIALOG_HOTEL_ROOMS_FREEOPTIONS);
					}
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_HOTEL_MAIN_OWNER);
			}
		}
		case DIALOG_HOTEL_ROOMS_OWNEDOPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:// Kick renter
					{
						// Kick
					}
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_HOTEL_ROOMS_LIST);
			}
		}
		case DIALOG_HOTEL_ROOMS_SETPRICE:
		{
			if (response)
			{
				MySQLQuery("UPDATE `hotelrooms` SET `Price` = '%s' WHERE `BuildingID` = '%d' AND `RoomID` = '%d'", MySQLEscapeString(inputtext), GetPVarInt(playerid, "DialogBuildingID"), GetPVarInt(playerid, "Hotel_Options_RoomID"));
			}
			ShowDialog(playerid, DIALOG_HOTEL_ROOMS_LIST);
		}
		case DIALOG_HOUSEOPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:// Enter
					{
						TeleportToBuilding(playerid, GetPVarInt(playerid, "DialogBuildingID"));
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
		case DIALOG_INBANK_JOB:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Bank Kaufen
					{
						SendClientMessage(playerid, COLOR_INFO, "Kaufen noch in Bearbeitung!");
					}
					case 1: // Konto Erstellen 
					{
						SendClientMessage(playerid, COLOR_INFO, "Konto erstellen noch in bearbeitung!");
					}
					case 2: // Konto übersicht 
					{
						SendClientMessage(playerid, COLOR_INFO, "Konto übersicht noch in Bearbeitung!");
					}
					case 3: // Konto Kündigen 
					{
						SendClientMessage(playerid, COLOR_INFO, "Konto Kündigen noch in Bearbeitung!");
					}
					case 4: // Aktueler Zinssatz
					{
						SendClientMessage(playerid, COLOR_INFO, "Zinssatz in bearbeitung!");
					}
					case 5: // Bewerben
					{
						SendClientMessage(playerid, COLOR_INFO, "Bewerben noch in Bearbeitung!");
					}
				}
			}
		}
		case DIALOG_INBANK_OPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Bank Sell
					{
						SendClientMessage(playerid, COLOR_INFO, "Bank verkaufen noch in Bearbeitung!");
					}
					case 1: // Bank Finanzen
					{
						SendClientMessage(playerid, COLOR_INFO, "Bank Finanzen noch in Bearbeitung!");
					}
					case 2: // Bewerbungs übersicht 
					{
						SendClientMessage(playerid, COLOR_INFO, "bewerbungs Übersicht noch in bearbeitung!");
					}
					case 3: // Eigene Konto Erstellen
					{
						SendClientMessage(playerid, COLOR_INFO, "Konto erstellen noch in Bearbeitung!");
					}
					case 4: // Eigenes Konto Übersicht 
					{
						SendClientMessage(playerid, COLOR_INFO, "Konto übersicht noch in Bearbeitung!");
					}
					case 5: // Konto Kündigen
					{
						SendClientMessage(playerid, COLOR_INFO, "Konto Kündigen noch in Bearbeitung!");
					}
					case 6: // Aktueler Zinssatz 
					{
						SendClientMessage(playerid, COLOR_INFO, "Zinssatz noch in Bearbeitung!");
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
					MySQLQuery("SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
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
					if (GetUserID(playerid))
					{
						MySQLQuery("UPDATE `users` SET `LoginTime` = NOW() WHERE `UserID` = '%d'", GetUserID(playerid));
						printf("Player logged in: %s (UserID: %d)", GetPlayerNameEx(playerid), GetUserID(playerid));
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
			if (response)
			{
				new modelID = strval(GetMySQLValue("vehiclemodels", "ModelID", "Name", inputtext));
				if (modelID)
				{
					MySQLQuery("INSERT INTO `missions` (`Name`, `CreatorUserID`) VALUES ('%s', '%d')", "%s abholen", playerid, MySQLEscapeString(inputtext));// TODO: Change name
					new missionID = mysql_insert_id();
					if (missionID)
					{
						MySQLQuery("INSERT INTO `missiondata` (`MissionID`, `Name`, `Value`) VALUES ('%d', 'Type', 'GetOrderedVehicle'), ('%d', 'VehicleModelID', '%d')", missionID, missionID, modelID);
						FormatNew:string[50]("Auftrag erstellt (Auftragsnummer: %d)", mysql_insert_id());
						SendClientMessage(playerid, COLOR_INFO, string);
					}
				}
			}
		}
		case DIALOG_POLICE_JOB:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Buy Police
					{
						SendClientMessage(playerid, COLOR_INFO, "Kaufen noch in Bearbeitung!");
					}
					case 1: // Bewerben by Police
					{
						if(GetJobID(playerid) >= 0)
						{
							SendClientMessage(playerid, COLOR_INFO, "Bewerben noch in Bearbeitung!");
						}
						else
						{
							SendClientMessage(playerid, COLOR_ERROR, "Du musst Zuerst einen beruf Kündigen!");
						}
					}
				}
			}
		}
		case DIALOG_POLICE_OPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Aufträge annehmen
					{
						ShowDialog(playerid, DIALOG_ACCEPT);
					}
					case 1: // Finanzen
					{
						SendClientMessage(playerid, COLOR_INFO, "Finanzen noch in Bearbeitung!");
					}
					case 2: // bewerbungs übersicht
					{
						SendClientMessage(playerid, COLOR_INFO, "bewerbung noch in Bearbeitung!");
					}
					case 3: // Job Kündigen
					{
						SendClientMessage(playerid, COLOR_INFO, "Kündigung noch in Bearbeitung!");
					}
				}
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
				new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][VEHICLEMODEL_MAXFUEL], vehicles[vehicleID][VEHICLE_CURRENTFUEL]);
				if (amount > maximum)
				{
					amount = maximum;
				}
				TogglePlayerControllable(playerid, false);
				SetVehicleEngineState(vehicleID, false);
				GameTextForPlayer(playerid, "Dein Fahrzeug wird getankt. Bitte warten...", 3000, 4);
				Timer_RefuelVehicle(playerid, amount);
			}
		}
		case DIALOG_REGISTER_GENDER:
		{
			if (response)
			{
				new gender;
				switch (listitem)
				{
					case 0:
					{
						gender = 'M';// Male
						SetPlayerSkin(playerid, REGISTER_SKIN_MALE);
					}
					case 1:
					{
						gender = 'F';// Female
						SetPlayerSkin(playerid, REGISTER_SKIN_FEMALE);
					}
				}
				MySQLQuery("INSERT INTO `users` (`Username`, `Password`, `Gender`, `RegisterTime`) VALUES ('%s', '%s', '%c', NOW())", MySQLEscapeString(GetPlayerNameEx(playerid)), MD5(GetPVarStringEx(playerid, "RegisterPassword")), gender);
				SetPVarInt(playerid, "UserID", mysql_insert_id());
				SavePlayer(playerid);
				printf("Player registered: %s (UserID: %d)", GetPlayerNameEx(playerid), GetUserID(playerid));
				SendClientMessage(playerid, COLOR_INFO, "Du wurdest erfolgreich registriert und bist nun eingeloggt.");
				TeleportTo(playerid, 1.7414, 31.6997, 1199.6012, 177.4850, 1, playerid);
				SetPlayerCheckpointEx(playerid, CHECKPOINT_WALKTOSEAT);
			}
			else
			{
				ShowDialog(playerid, DIALOG_REGISTER_PASSWORD2);
			}
		}
		case DIALOG_REGISTER_PASSWORD1:
		{
			if (response)
			{
				if (strlen(inputtext) >= REGISTER_PASSWORD_MIN && strlen(inputtext) <= REGISTER_PASSWORD_MAX)
				{
					SetPVarString(playerid, "RegisterPassword", inputtext);
					ShowDialog(playerid, DIALOG_REGISTER_PASSWORD2);
				}
				else
				{
					FormatNew:string[80]("Bitte verwende ein Passwort mit einer Länge zwischen %d und %d Zeichen!", REGISTER_PASSWORD_MIN, REGISTER_PASSWORD_MAX);
					SendClientMessage(playerid, COLOR_ERROR, string);
					ShowDialog(playerid, DIALOG_REGISTER_PASSWORD1);
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_INFO, "Du kannst nun das Spiel beenden!");
				Kick(playerid);
			}
		}
		case DIALOG_REGISTER_PASSWORD2:
		{
			if (response)
			{
				if (!strcmp(inputtext, GetPVarStringEx(playerid, "RegisterPassword")))
				{
					ShowDialog(playerid, DIALOG_REGISTER_GENDER);
				}
				else
				{
					SendClientMessage(playerid, COLOR_ERROR, "Die eingegebenen Passwörter stimmen nicht überein! Bitte versuche es erneut.");
					ShowDialog(playerid, DIALOG_REGISTER_PASSWORD1);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_REGISTER_PASSWORD1);
			}
			return true;
		}
		case DIALOG_RESTARTGAMEMODE:
		{
			if (response)
			{
				for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
				{
					SavePlayer(playerID);
				}
				SendClientMessage(playerid, COLOR_INFO, "Du hast den Gamemode neugestartet");
				FormatNew:string[60]("%s hat den Gamemode neugestartet", GetPlayerNameEx(playerid));
				SendClientMessageToAllExcept(playerid, COLOR_INFO, string);
				SendRconCommand("gmx");
			}
		}
		case DIALOG_STATS:
		{
			if (response)
			{
				return COMMAND_OK;
			}
		}
		case DIALOG_SELECTINTERIOR:
		{
			new interiorDialogID = GetPVarInt(playerid, "InteriorDialogID");
			new interiorID;
			if (!response)
			{
				DeletePVar(playerid, "InteriorDialogID");
				OnInteriorDialogSelect(playerid, interiorDialogID, 0);
				return true;
			}
			if (!strcmp(inputtext, "Zurück", true))
			{
				ShowDialog(playerid, DIALOG_SELECTINTERIOR, interiorDialogID, 0);
				return true;
			}
			if (!strcmp(inputtext, "Weiter", true))
			{
				ShowDialog(playerid, DIALOG_SELECTINTERIOR, interiorDialogID, 75);
				return true;
			}
			interiorID = strval(GetMySQLValue("interiors", "ID", "Name", inputtext));
			DeletePVar(playerid, "InteriorDialogID");
			if (!interiorID)
			{
				SendClientMessage(playerid, COLOR_ERROR, "Ungültige Auswahl!");
			}
			OnInteriorDialogSelect(playerid, interiorDialogID, interiorID);
		}
		case DIALOG_TELEPORTLOCATIONS:
		{
			if (response)
			{
				MySQLQuery("SELECT * FROM `teleports` WHERE `Name` = '%s'", MySQLEscapeString(inputtext));
				mysql_store_result();
				if (mysql_num_rows())
				{
					Teleport(playerid, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")), 0, strval(GetMySQLField("Interior")), 0);
				}
				mysql_free_result();
			}
		}
		case DIALOG_TRUCKER_JOB:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Kaufe Trucker
					{
						// TODO: MySQL Daten bank hinzufügen bei Jobs die OwnerUserID zum kaufen.
						SendClientMessage(playerid, COLOR_INFO, "Kaufen in Bearbeitung!");
					}
					case 1: // Bewerben für den Job Trucker
					{
						if(GetJobID(playerid) >= 0)
						{
							// TODO: MySQL DB erstellen für Bewerbung jeglicher Jobarten.
							// TODO: Diese der Owner des Jobs bearbeiten kann anneehmen kann und ablehnen kann.
							SendClientMessage(playerid, COLOR_INFO, "Bewerben noch in Bearbeitung!");
						}
						else
						{
							SendClientMessage(playerid, COLOR_ERROR, "Du musst Zuerst einen beruf Kündigen!");
						}
					}
				}
			}
		}
		case DIALOG_TRUCKER_OPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Aufträge
					{
						ShowDialog(playerid, DIALOG_ACCEPT);
					}
					case 1: // Finanzen
					{
						// TODO: Finanzen für jeden Job erstellen: Job Guthaben
						SendClientMessage(playerid, COLOR_INFO, "Finanzen in Bearbeitung");
					}
					case 2: // Kündigen
					{
						SendClientMessage(playerid, COLOR_INFO, "KÜndigung noch in Bearbeitung!");
					}
					case 3: // Bewerbungs übersicht
					{
						SendClientMessage(playerid, COLOR_INFO, "Bewerbungs übersicht in bearbeitung!");
					}
				}
			}
		}
		case DIALOG_VEHICLEDEALER_JOB:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Kaufe Autohändler
					{
						// TODO: MySQL Daten bank hinzufügen bei Jobs die OwnerUserID zum kaufen.
						SendClientMessage(playerid, COLOR_INFO, "Kaufen in bearbeitung!");
					}
					case 1: // Bewerben für den job
					{
						if(GetJobID(playerid) >= 0)
						{
							// TODO: MySQL DB erstellen für Bewerbung jeglicher Jobarten.
							// TODO: Diese der Owner des Jobs bearbeiten kann anneehmen kann und ablehnen kann.
							SendClientMessage(playerid, COLOR_INFO, "Bewerben noch in Bearbeitung!");
						}
						else
						{
							SendClientMessage(playerid, COLOR_ERROR, "Du musst Zuerst einen beruf Kündigen!");
						}
					}
					case 2:
					{
						// TODO: noch am überlegen wie es gestaltet werden soll. 
						// TODO: eventuel Wen auto nicht da anfordern beim Autohändler zum bestellen.
						SendClientMessage(playerid, COLOR_INFO, "Fahrzeug kaufen in Bearbeitung!");
					}
				}
			}
		}
		case DIALOG_VEHICLEDEALER_OPTIONS:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0: // Fahrzeug Bestellen
					{
						ShowDialog(playerid, DIALOG_ORDERVEHICLE);
					}
					case 1: // Finazübersicht
					{
						// TODO: Jeder Job hat eine Job Kasse in der DB diese hier abgerufen wird.
						SendClientMessage(playerid, COLOR_INFO, "Finanzen in Bearbeitung!");
					}
					case 2: // Kündigen
					{
						// TODO: Kündigung seines Jobs
						SendClientMessage(playerid, COLOR_INFO, "Kündigen in Bearbeitung!");
					}
					case 3: // Bewerbungs übrsicht
					{
						// TODO: MySQL DB abrufen für Bewerbungen vom AUtohändler dort kann man Annehmen/Ablehnen ist angenommen wird invitet ist abgelehnt bleibt user so.
						SendClientMessage(playerid, COLOR_INFO, "Bewerbung in bearbeitung!");
					}
				}
			}
		}
	}
	return false;
}