public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		/*case DIALOG_ADDHOTELROOM:
		{
			if (response)
			{
				if(!strcmp(inputtext, "Zur�ck", true))
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
						new string[256];
						new name[256];
						new hotel[256];
						new Float: PosX;
						new Float: PosY;
						new Float: PosZ;
						GetPvarString(playerid, "AddHotel_Name", name, sizeof(name));
						GetPlayerPos(playerid, PosX, PosY, PosZ);
						new pickupID = AddPickup(-1, "HOTELROOM", PosX, PosY, PosZ, true);
						if(pickupID > 0)
						{
							MySQLQuery("INSERT INTO `buildings` (`PickupID`, `InteriorID`, `Name`, `HotelOwner`) VALUES ('%d', '%s', '%s', '%s')", pickupID, GetMySQLValue("interior", "ID", "Name", inputtext), name, hotel);
							Format:string("Das Hotel Zimmer %s (Hotel: %s) wurde mit dem Ziel %s verkn�pft und unter der ID %d gespeichert.", name, hotel, inputtext, mysql_insert_id());
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
				new string[256];
				new Float:posX;
				new Float:posY;
				new Float:posZ;
				new buildingID;
				new pickupID;
				GetPlayerPos(playerid, posX, posY, posZ);
				pickupID = AddPickup(-1, GetPVarStringEx(playerid, "AddBuilding_Type"), posX, posY, posZ, true);
				if (pickupID > 0)
				{
					MySQLQuery("INSERT INTO `buildings` (`PickupID`, `InteriorID`, `Name`, `Price`) VALUES ('%d', '%d', '%s', '%f')", pickupID, GetPVarInt(playerid, "AddBuilding_InteriorID"), MySQLEscapeString(inputtext), GetPVarFloat(playerid, "AddBuilding_Price"));
					buildingID = mysql_insert_id();
					SetPVarInt(playerid, "LastAddedBuilding", buildingID);
					Format:string("Das Geb�ude %s (Preis: %s) wurde unter der ID %d gespeichert.", inputtext, FormatMoney(GetPVarFloat(playerid, "AddBuilding_Price")), buildingID);
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
				new type[256];
				switch (listitem)
				{
					case 0:
						Format:type("BANK");
					case 1:
						Format:type("HOTEL");
					case 2:
						Format:type("HOUSE");
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
				new string[256];
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
					format(string,sizeof(string), "Du ben�tigst $%s f�r dieses Fahrzeug! Leider hast du nur $%s.", FormatMoney(price), FormatMoney(GetPlayerMoneyEx(playerid)));
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
					SendClientMessage(playerid, COLOR_INFO, "Viel Spa� mit deinem neuen Haus");
				}
				else
				{
					new string[256];
					format(string,sizeof(string), "Du ben�tigst $%s f�r dieses Haus! Leider hast du nur $%s.", FormatMoney(price), FormatMoney(GetPlayerMoneyEx(playerid)));
					SendClientMessage(playerid, COLOR_ERROR, string);
				}
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
							SendClientMessage(playerid, COLOR_INFO, "Viel Spa� mit deinem neuen Hotel");
							ShowDialog(playerid, DIALOG_HOTEL_MAIN_OWNER);
						}
						else
						{
							new string[256];
							format(string,sizeof(string), "Du ben�tigst $%s f�r dieses Hotel! Leider hast du nur $%s.", FormatMoney(price), FormatMoney(GetPlayerMoneyEx(playerid)));
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
						SendClientMessage(playerid, COLOR_SYSTEM, "K�ndigen");
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
						SendClientMessage(playerid, COLOR_ERROR, "Ung�ltige Auswahl!");
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
					GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);
					MySQLQuery("SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(playerName));
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
						printf("Player logged in: %s (UserID: %d)", playerName, GetUserID(playerid));
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
					Format:string("Bitte verwende ein Passwort mit einer L�nge zwischen %d und %d Zeichen!", REGISTER_MINPASSWORD, REGISTER_MAXPASSWORD);
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
					new playerName[MAX_PLAYER_NAME];
					GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);
					MySQLQuery("INSERT INTO `users` (`Username`, `Password`, `RegisterTime`) VALUES ('%s', '%s', NOW())", MySQLEscapeString(playerName), MD5(inputtext));
					SetPVarInt(playerid, "UserID", mysql_insert_id());
					SavePlayer(playerid);
					SetPVarInt(playerid, "AllowSkinSelection", true);
					printf("Player registered: %s (UserID: %d)", playerName, GetUserID(playerid));
					SendClientMessage(playerid, COLOR_INFO, "Du wurdest erfolgreich registriert und bist nun eingeloggt.");
					SendClientMessage(playerid, COLOR_INFO, "Bitte w�hle deinen Spieler aus.");
				}
				else
				{
					SendClientMessage(playerid, COLOR_ERROR, "Die eingegebenen Passw�rter stimmen nicht �berein! Bitte versuche es erneut.");
					ShowDialog(playerid, DIALOG_REGISTER_STEP1);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_REGISTER_STEP1);
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
				new string[256];
				Format:string("%s hat den Gamemode neugestartet");
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
			if (!strcmp(inputtext, "Zur�ck", true))
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
				SendClientMessage(playerid, COLOR_ERROR, "Ung�ltige Auswahl!");
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
	}
	return false;
}