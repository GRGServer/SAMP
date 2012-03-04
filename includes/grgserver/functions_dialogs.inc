ShowDialog(playerID, dialogID, ...)
{
	switch (dialogID)
	{
		case DIALOG_ACCEPT:
		{
			new missionList[2048];
			MySQLQuery("SELECT * FROM `missions` WHERE `JobID` = '%d' AND `AcceptUserID` = '0' ORDER BY `Name` ASC", GetPVar:playerID[JOBID]);
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(missionList))
				{
					Format:missionList("%s\n", missionList);
				}
				Format:missionList("%s%s: %s", missionList, GetMySQLField("ID"), GetMySQLField("Name"));
			}
			mysql_free_result();
			if (strlen(missionList))
			{
				ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Auftragsannahme", missionList, "Annehmen", "Abbrechen");
			}
			else
			{
				SendClientMessage(playerID, COLOR_ERROR, "Es stehen derzeit keine Aufträge in deinem Beruf zur Verfügung!");
			}
		}
		case DIALOG_ADDBUILDING_NAME:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, "Name eingeben", "Gebe den Name für das Gebäude ein.", "Erstellen", "Zurück");
		}
		case DIALOG_ADDBUILDING_TYPE:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Gebäudetyp auswählen", "Bank\nHotel\nHaus\nPolizei", "Weiter", "Abbrechen");
		}
		case DIALOG_BUYHOUSE:
		{
			new string[70];
			GetStringArg(2, string);
			Format:string("Dieses Haus kann noch gekauft werden.\n\nPreis: $%s", string);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_MSGBOX, "Haus kaufen", string, "Kaufen", "Abbrechen");
		}
		case DIALOG_BUYVEHICLE:
		{
			new string[70];
			GetStringArg(2, string);
			Format:string("Möchtest du dieses Fahrzeug Kaufen?\n\nPreis: $%s", string);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_MSGBOX, "Fahrzeug Kaufen", string, "Ja", "Nein");
		}
		case DIALOG_CHANGEPASSWORD_STEP1:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Accountpasswort ändern", "Gebe dein aktuelles Passwort ein.", "Weiter", "Abbrechen");
		}
		case DIALOG_CHANGEPASSWORD_STEP2:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Accountpasswort ändern", "Gebe ein neues Passwort ein.", "Weiter", "Zurück");
		}
		case DIALOG_CHANGEPASSWORD_STEP3:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Accountpasswort ändern", "Wiederhole zur Sicherheit dein neues Passwort.", "OK", "Zurück");
		}
		case DIALOG_HOTEL_MAIN_AVAILABLE:
		{
			FormatNew:options[40]("Hotel kaufen"); // Item 0
			Format:options("%s\nZimmer mieten", options); // Item 1
			Format:options("%s\nBetreten", options); // Item 2
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hotel", options, "OK", "Abbrechen");
		}
		case DIALOG_HOTEL_MAIN_BOUGHT:
		{
			FormatNew:options[30]("Betreten"); // Item 0
			Format:options("%s\nMieten", options); // Item 1
			Format:options("%s\nKündigen", options); // item 2
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hoteloptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_HOTEL_MAIN_OWNER:
		{
			FormatNew:options[50]("Betreten"); // Item 0
			Format:options("%s\nVerkaufen", options); // Item 1
			Format:options("%s\nEinnahmen", options); // item 2
			Format:options("%s\nZimmeroptionen", options); // Item 3
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hoteloptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_HOTEL_ROOMS_FREEOPTIONS:
		{
			FormatNew:options[20]("Mietpreis festlegen"); // Item 0
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Zimmeroptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_HOTEL_ROOMS_LIST:
		{
			new rooms[2048];
			new string[MAX_PLAYER_NAME];
			MySQLQuery("SELECT `RoomID`, `Username` FROM `hotelrooms` LEFT JOIN `users` ON `hotelrooms`.`OwnerUserID` = `users`.`UserID` WHERE `hotelrooms`.`BuildingID` = '%d' ORDER BY `RoomID` ASC", GetPVar:playerID[DIALOGBUILDINGID]);
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(rooms))
				{
					Format:rooms("%s\n", rooms);
				}
				if (strlen(GetMySQLField("Username")))
				{
					Format:string(GetMySQLField("Username"));
				}
				else
				{
					Format:string("[Leer]");
				}
				Format:rooms("%%s: %s", GetMySQLField("RoomID"), string);
			}
			mysql_free_result();
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Zimmer wählen", rooms, "Optionen", "Abbrechen");
		}
		case DIALOG_HOTEL_ROOMS_OWNEDOPTIONS:
		{
			new options[20];
			Format:options("Mieter rauswerfen", options); // Item 0
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Zimmeroptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_HOUSEOPTIONS:
		{
			FormatNew:options[20]("Betreten");// Item 0
			Format:options("%s\nVerkaufen", options);// Item 1
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hausoptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_INBANK_JOB:
		{
			FormatNew:options[90]("Bank Kaufen");
			Format:options("%s\nKonto Erstellen", options);
			Format:options("%s\nKonto Übersicht", options);
			Format:options("%s\nKonto Kündigen", options);
			Format:options("%s\nAktueler Zinssatz", options);
			Format:options("%s\nBewerben", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Bank", options, "OK", "Abbrechen");
		}
		case DIALOG_INBANK_OPTIONS:
		{
			FormatNew:options[150]("Bank Verkaufen");
			Format:options("%s\nFinazen Übersicht", options);
			Format:options("%s\nBewerbungs Übersicht", options);
			Format:options("%s\nEigenes Konto Erstellen", options);
			Format:options("%s\nEigene Konto Übersicht", options);
			Format:options("%s\nEigenes Konto Kündigen", options);
			Format:options("%s\nAktueler Zinssatz", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Bank", options, "OK", "Abbrechen");
		}
		case DIALOG_LOGIN:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Login", "Bitte gebe das Passwort von deinen Account ein.", "OK", "Abbrechen");
		}
		case DIALOG_ORDERVEHICLE:
		{
			new vehicleList[2048];
			mysql_query("SELECT * FROM `vehiclemodels` ORDER BY `Name` ASC");
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(vehicleList))
				{
					Format:vehicleList("%s\n", vehicleList);
				}
				Format:vehicleList("%s%s", vehicleList, GetMySQLField("Name"));
			}
			mysql_free_result();
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Fahrzeug bestellen", vehicleList, "Bestellen", "Abbrechen");
		}
		case DIALOG_POLICE:
		{
			FormatNew:options[10]("Betreten");
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Polizei", options, "OK", "Abbrechen");
		}
		case DIALOG_POLICE_JOB:
		{
			FormatNew:options[40]("Polizeirevier kaufen");
			Format:options("%s\nBewerben", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Polizei", options, "OK", "Abbrechen");
		}
		case DIALOG_POLICE_OPTIONS:
		{
			FormatNew:options[50]("Aufträge");
			Format:options("%s\nFinazen", options);
			Format:options("%s\nBewerbungsübersicht", options);
			Format:options("%s\nKündigen", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Polizei", options, "OK", "Abbrechen");
		}
		case DIALOG_RADIO:
		{
			new stations[2048];
			mysql_query("SELECT * FROM `radiostations`");
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(stations))
				{
					Format:stations("%s\n", stations);
				}
				Format:stations("%s%s", stations, GetMySQLField("Name"));
			}
			mysql_free_result();
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Radiosender wählen", stations, "OK", "Abbrechen");
		}
		case DIALOG_REFUEL:
		{
			new string[80];
			GetStringArg(2, string);
			SetPVar:playerID[CURRENTGASPRICE](gasPrice);
			Format:string("Wie viel möchtest du tanken (0 - %s)?\n\nAktueller Preis: $%s/Liter", string, FormatMoney(gasPrice));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, "Tanken", string, "Tanken", "Abbrechen");
		}
		case DIALOG_REGISTER_GENDER:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Geschlecht auswählen", "Männlich\nWeiblich", "OK", "Zurück");
		}
		case DIALOG_REGISTER_PASSWORD1:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Registrieren", "Du bist noch nicht registriert!\nBitte gebe ein neues Passwort für deinen Account ein.", "Weiter", "Abbrechen");
		}
		case DIALOG_REGISTER_PASSWORD2:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Passwort wiederholen", "Wiederhole zur Sicherheit dein neues Passwort.", "Weiter", "Zurück");
		}
		case DIALOG_RESTARTGAMEMODE:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_MSGBOX, "Gamemode neustarten", "Soll der Gamemode wirklich neugestartet werden?", "Ja", "Nein");
		}
		case DIALOG_SELECTINTERIOR:
		{
			new interiors[2048];
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
			MySQLQuery("SELECT * FROM `interiors` ORDER BY `Name` ASC LIMIT %d,75", startID);
			mysql_store_result();
			while (FetchMySQLRow())
			{
				if (strlen(interiors))
				{
					Format:interiors("%s\n", interiors);
				}
				Format:interiors("%s%s", interiors, GetMySQLField("Name"));
			}
			mysql_free_result();
			switch (page)
			{
				case 1:
				{
					Format:interiors("%s\nWeiter", interiors);
				}
				case 2:
				{
					Format:interiors("%s\nZurück", interiors);
				}
			}
			FormatNew:string[30]("Ziel auswählen (Seite %d)", page);
			SetPVar:playerID[INTERIORDIALOGID](getarg(2));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, string, interiors, "OK", "Abbrechen");
		}
		case DIALOG_STATS:
		{
			new string[1024];
			Format:string("SELECT `users`.`UserID`, `users`.`Username`, UNIX_TIMESTAMP(`users`.`BirthDate`) AS `BirthDate`, `users`.`Location`, `users`.`MobilePhoneNumber`, `users`.`BankID`, `users`.`JobID`, `users`.`OnlineTime`, `users`.`LoginTime`, `banks`.`Name` AS `Bank`, `jobs`.`Name` AS `JobName` FROM `users`");
			MySQLQuery("%s LEFT JOIN (`banks`, `jobs`) ON (`banks`.`ID` = `users`.`BankID` AND `jobs`.`ID` = `users`.`JobID`) WHERE `users`.`UserID` = '%d'", string, GetPVar:playerID[USERID]);
			mysql_store_result();
			Format:string("ID:\t%s", GetMySQLField("UserID"));
			Format:string("%s\nName:\t%s", string, GetMySQLField("Username"));
			Format:string("%s\nAlter:\t%d Jahre", string, CalculateAge(strval(GetMySQLField("BirthDate"))));
			Format:string("%s\nWohnort:\t%s", string, GetMySQLField("Location"));
			Format:string("%s\nHandynummer:\t%s", string, GetMySQLField("MobilePhoneNumber"));
			if (strval(GetMySQLField("BankID")))
			{
				Format:string("%s\nBank:\t%s", string, GetMySQLField("Bank"));
			}
			Format:string("%s\nGuthaben:\t$%s", string, FormatMoney(GetPVar:playerID[MONEY]));
			if (strval(GetMySQLField("JobID")))
			{
				Format:string("%s\nBeruf:\t%s", string, GetMySQLField("JobName"));
			}
			Format:string("%s\nSpielzeit:\t%s", string, FormatTime(strval(GetMySQLField("OnlineTime"))));
			Format:string("%s\nLetzter Login:\t%s", string, FormatDate(GetMySQLField("LoginTime")));
			mysql_free_result();
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_MSGBOX, "Personalien", string, "OK", "");
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
					Format:locations("%s\n", locations);
				}
				Format:locations("%s%s", locations, GetMySQLField("Name"));
			}
			mysql_free_result();
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Teleportieren", locations, "OK", "Abbrechen");
		}
		case DIALOG_TRUCKER_JOB:
		{
			FormatNew:options[30]("Truckerfirma kaufen");
			Format:options("%s\nBewerben", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Trucker", options, "OK", "Abbrechen");
		}
		case DIALOG_TRUCKER_OPTIONS:
		{
			FormatNew:options[50]("Aufträge");
			Format:options("%s\nFinanzen", options);
			Format:options("%s\nKündigen", options);
			Format:options("%s\nBewerbungsübersicht", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Trucker Übersicht", options, "OK", "Abbrechen");
		}
		case DIALOG_VEHICLEDEALER_JOB:
		{
			new options[50];
			Format:options("Autohändler kaufen");
			Format:options("%s\nBewerben", options);
			Format:options("%s\nFahrzeug Kaufen", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Autohändler", options, "OK", "Abbrechen");
		}
		case DIALOG_VEHICLEDEALER_OPTIONS:
		{
			new options[70];
			Format:options("Fahrzeug bestellen");
			Format:options("%s\nFinanzen", options);
			Format:options("%s\nKündigen", options);
			Format:options("%s\nBewerbungsübersicht", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Autohändlerübersicht", options, "OK", "Abbrechen");
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
				SetPVar:playerID[ADDBUILDING_INTERIORID](interiorID);
				ShowDialog(playerID, DIALOG_ADDBUILDING_NAME);
			}
			else
			{
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