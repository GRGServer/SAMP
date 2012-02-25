ShowDialog(playerID, dialogID, ...)
{
	switch (dialogID)
	{
		case DIALOG_ADDBUILDING_NAME:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, "Name eingeben", "Gebe den Name für das Gebäude ein.", "Erstellen", "Zurück");
		}
		case DIALOG_ADDBUILDING_TYPE:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Gebäudetyp auswählen", "Bank\nHotel\nHaus", "Weiter", "Abbrechen");
		}
		case DIALOG_BUYHOUSE:
		{
			new string[256];
			new price[256];
			GetStringArg(2, price);
			format(string, sizeof(string), "Dieses Haus kann noch gekauft werden.\n\nPreis: %s", price);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_MSGBOX, "Haus kaufen", string, "Kaufen", "Abbrechen");
		}
		case DIALOG_BUYVEHICLE:
		{
			new string[256];
			new price[256];
			GetStringArg(2, price);
			format(string, sizeof(string), "Möchtest du dieses Fahrzeug Kaufen?\nDies kostet $%s", price);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_MSGBOX, "Fahrzeug Kaufen", string, "Ja", "Nein");
		}
		case DIALOG_HOTEL_MAIN_AVAILABLE:
		{
			new options[1024];
			format(options, sizeof(options), "Hotel Kaufen"); // Item 0
			format(options, sizeof(options), "%s\nZimmer Mieten", options); // Item 1
			format(options, sizeof(options), "%s\nBetreten", options); // Item 2
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hotel", options, "OK", "Abbrechen");
		}
		case DIALOG_HOTEL_MAIN_BOUGHT:
		{
			new options[1024];
			format(options, sizeof(options), "Betreten"); // Item 0
			format(options, sizeof(options), "%s\nMieten", options); // Item 1
			format(options, sizeof(options), "%s\nKündigen", options); // item 2
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hoteloptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_HOTEL_MAIN_OWNER:
		{
			new options[1024];
			format(options, sizeof(options), "Betreten"); // Item 0
			format(options, sizeof(options), "%s\nVerkaufen", options); // Item 1
			format(options, sizeof(options), "%s\nEinnahmen", options); // item 2
			format(options, sizeof(options), "%s\nZimmeroptionen", options); // Item 3
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hoteloptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_HOTEL_ROOMS_FREEOPTIONS:
		{
			new options[1024];
			format(options, sizeof(options), "Mietpreis festlegen"); // Item 0
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Zimmeroptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_HOTEL_ROOMS_LIST:
		{
			new query[256];
			new rooms[2048];
			new string[256];
			format(query, sizeof(query), "SELECT `RoomID`, `Username` FROM `hotelrooms` LEFT JOIN `users` ON `hotelrooms`.`OwnerUserID` = `users`.`UserID` WHERE `hotelrooms`.`BuildingID` = '%d' ORDER BY `RoomID` ASC", GetPVarInt(playerID, "DialogBuildingID"));
			mysql_query(query);
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(rooms))
				{
					format(rooms, sizeof(rooms), "%s\n", rooms);
				}
				if (strlen(GetMySQLField("Username")))
				{
					format(string, sizeof(string), GetMySQLField("Username"));
				}
				else
				{
					format(string, sizeof(string), "[Leer]");
				}
				format(rooms, sizeof(rooms), "%%s: %s", GetMySQLField("RoomID"), string);
			}
			mysql_free_result();
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Zimmer wählen", rooms, "Optionen", "Abbrechen");
		}
		case DIALOG_HOTEL_ROOMS_OWNEDOPTIONS:
		{
			new options[1024];
			format(options, sizeof(options), "Mieter rauswerfen", options); // Item 0
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Zimmeroptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_HOUSEOPTIONS:
		{
			new options[1024];
			format(options, sizeof(options), "Betreten");// Item 0
			format(options, sizeof(options), "%s\nVerkaufen", options);// Item 1
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hausoptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_LOGIN:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Login", "Bitte gebe das Passwort von deinen Account ein.", "OK", "Abbrechen");
		}
		case DIALOG_ORDERVEHICLE:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Fahrzeug bestellen", "Landstalker\nBravura\nBuffalo\nLinerunner\nPerenniel\nSentinel\nFiretruck", "Bestellen", "Abbrechen");
		}
		case DIALOG_RADIO:
		{
			new stations[1024];
			mysql_query("SELECT * FROM `radiostations`");
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(stations))
				{
					format(stations, sizeof(stations), "%s\n", stations);
				}
				format(stations, sizeof(stations), "%s%s", stations, GetMySQLField("Name"));
			}
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Radiosender wählen", stations, "OK", "Abbrechen");
		}
		case DIALOG_REFUEL:
		{
			new string[256];
			new maximum[256];
			GetStringArg(2, maximum);
			format(string, sizeof(string), "Wie viel möchtest du tanken (0 - %s)?", maximum);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, "Tanken", string, "Tanken", "Abbrechen");
		}
		case DIALOG_REGISTER_STEP1:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Registrieren", "Du bist noch nicht registriert!\nBitte gebe ein neues Passwort für deinen Account ein.", "OK", "Abbrechen");
		}
		case DIALOG_REGISTER_STEP2:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Passwort wiederholen", "Gebe erneut das Passwort ein.", "Registrieren", "Zurück");
		}
		case DIALOG_RESTARTGAMEMODE:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_MSGBOX, "Gamemode neustarten", "Soll der Gamemode wirklich neugestartet werden?", "Ja", "Nein");
		}
		case DIALOG_STATS:
		{
			new name[MAX_PLAYER_NAME];
			new old = 18;
			new home = "Evergreen Therrens 1";
			new perso = 829107936;
			new veh1 = "BMW M3 Schnitzer";
			new veh2 = "Audi R8";
			new veh3 = "Nissan Silvia";
			new veh4 = "Toyota Supra";
			new bank = 16220;
			new hand = 16220;
			new Float:Zins = 1.5;
			new konto = 1335202;
			new job = "Autohändler";
			new gametime = 15;
			new date = 12;
			new number = 1338;
			new MSGBOX[1028];
			format(MSGBOX, sizeof(MSGBOX), "Name:\t%s\nAlter:\t%d\nWohnort:\t%s\nPersonal Nummer:\t%s\n",name, old, home,perso);
			format(MSGBOX, sizeof(MSGBOX), "%s\n\nBesitzende Fahrzeuge:\t%s\n\t%s\n\t%s\n\t%s",MSGBOX,veh1,veh2,veh3,veh4);
			format(MSGBOX, sizeof(MSGBOX), "%s\n\nGuthaben:\nBank:\t%d\nTasche:\t%d\nZinssatz:\t%f\nKontoNummer:\t%d",MSGBOX,bank,hand,zins,konto);
			format(MSGBOX, sizeof(MSGBOX), "%s\n\nBeruf:\t%s\n\n\nSpielzeit:\t%d\nLetzter Login:\t%d\nHandy Nummer:\t%d",MSGBOX,job,gametime,date,number);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_MSGBOX, "Personalien", MSGBOX, "OK","");
		}
		case DIALOG_SELECTINTERIOR:
		{
			new interiors[2048];
			new string[256];
			new query[256];
			new startID = getarg(3);
			new page;
			if (startID)
			{
				page = 2;
			}
			else
			{
				page = 1;
			}
			format(query, sizeof(query), "SELECT * FROM `interiors` ORDER BY `Name` ASC LIMIT %d,75", startID);
			mysql_query(query);
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(interiors))
				{
					format(interiors, sizeof(interiors), "%s\n", interiors);
				}
				format(interiors, sizeof(interiors), "%s%s", interiors, GetMySQLField("Name"));
			}
			mysql_free_result();
			switch (page)
			{
				case 1:
				{
					format(interiors, sizeof(interiors), "%s\nWeiter", interiors);
				}
				case 2:
				{
					format(interiors, sizeof(interiors), "%s\nZurück", interiors);
				}
			}
			format(string, sizeof(string), "Ziel auswählen (Seite %d)", page);
			SetPVarInt(playerID, "InteriorDialogID", getarg(2));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, string, interiors, "OK", "Abbrechen");
		}
		case DIALOG_TELEPORTLOCATIONS:
		{
			new locations[2048];
			mysql_query("SELECT * FROM `teleports`");
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(locations))
				{
					format(locations, sizeof(locations), "%s\n", locations);
				}
				format(locations, sizeof(locations), "%s%s", locations, GetMySQLField("Name"));
			}
			mysql_free_result();
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Teleportieren", locations, "OK", "Abbrechen");
		}
	}
}

ShowInteriorDialog(playerID, dialogID)
{
	ShowDialog(playerID, DIALOG_SELECTINTERIOR, dialogID, 0);
}

OnInteriorDialogSelect(playerID, dialogID, interiorID)
{
	switch (dialogID)
	{
		case INTERIORDIALOG_ADDBUILDING:
		{
			if (interiorID)
			{
				SetPVarInt(playerID, "AddBuilding_InteriorID", interiorID);
				ShowDialog(playerID, DIALOG_ADDBUILDING_NAME);
			}
			else
			{
				DeletePVar(playerID, "AddBuilding_Type");
				ShowDialog(playerID, DIALOG_ADDBUILDING_TYPE);
			}
		}
		case INTERIORDIALOG_SHOWINTERIOR:
		{
			if (interiorID)
			{
				if (TeleportToInterior(playerID, interiorID))
				{
					SetPlayerVirtualWorld(playerID, 0);
				}
			}
		}
	}
}