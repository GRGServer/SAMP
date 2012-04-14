ShowDialog(playerID, dialogID, ...)
{
	switch (dialogID)
	{
		/*
			Accept a job created via the following:
			- DIALOG_ORDERVEHICLE
		*/
		case DIALOG_ACCEPT:
		{
			new missionList[2048];
			MySQLQuery("SELECT * FROM `missions` WHERE `JobID` = '%d' AND `AcceptUserID` = '0' ORDER BY `Name` ASC", PVar:playerID[JOBID]);
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
				ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 163), missionList, LanguageString(playerID, 164), LanguageString(playerID, 165));
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 134);
			}
		}
		case DIALOG_ADAC:
		{
			FormatNew:options[50]("%s\n%s", LanguageString(playerID, 217), LanguageString(playerID, 218));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 219), options, LanguageString(playerID, 177), LanguageString(playerID, 165));
		}
		case DIALOG_ARMEE:
		{
			FormatNew:options[50]("%s\n%s", LanguageString(playerID, 217), LanguageString(playerID, 218));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 220), options, LanguageString(playerID, 177), LanguageString(playerID, 165));
		}
		case DIALOG_AMBULANCE:
		{
			FormatNew:options[50]("%s\n%s", LanguageString(playerID, 217), LanguageString(playerID, 218));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 221), options, LanguageString(playerID, 177), LanguageString(playerID, 165));
		}
		// Enter name of the new building
		case DIALOG_ADDBUILDING_NAME:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, LanguageString(playerID, 168), LanguageString(playerID, 169), LanguageString(playerID, 170), LanguageString(playerID, 171));
		}
		// Select type of the new building
		case DIALOG_ADDBUILDING_TYPE:
		{
			FormatNew:options[50]("%s\n%s\n%s\n%s", LanguageString(playerID, 173), LanguageString(playerID, 174), LanguageString(playerID, 175), LanguageString(playerID, 176));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 172), options, LanguageString(playerID, 177), LanguageString(playerID, 165));
		}
		// ???
		case DIALOG_APPLICATION_PLAYER:
		{
			// TODO: Can not work!
			MySQLQuery("SELECT * FROM `application` WHERE `ID` = '%d' ORDER BY `UserName` ASC", PVar:playerID[APPLICATIONID]);
			mysql_store_result();
			while (FetchMySQLRow())
			{
				new UserName[MAX_PLAYER_NAME];//SPAAAAAAAAAAAAAAAAAAAAAAACEEEEEE
				FormatNew:string[100]("%s: %s\n", LanguageString(playerID, 178), UserName);
				ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Bewerbungs Übersicht", string, "Anschauen", LanguageString(playerID, 165));
			}
			mysql_free_result();
		}
		// Cancel the bank account
		case DIALOG_BANK_CANCELACCOUNT:
		{
			ShowMsgBox(playerID, dialogID, LanguageString(playerID, 209), LanguageString(playerID, 214), MSGBOXSTYLE_YESNO);
		}
		// Deposit money to the bank account
		case DIALOG_BANK_DEPOSITMONEY:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, LanguageString(playerID, 208), LanguageString(playerID, 212), "OK", LanguageString(playerID, 165));
		}
		// Show options for the bank account
		case DIALOG_BANK_HASACCOUNT:
		{
			new options[1024];
			AddLine(options, LanguageString(playerID, 206));// Bank balance
			AddLine(options, LanguageString(playerID, 207));// Withdraw money
			AddLine(options, LanguageString(playerID, 208));// Deposit money
			AddLine(options, LanguageString(playerID, 209));// Cancel account
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Bank", options, "OK", LanguageString(playerID, 165));
		}
		// Ask to create a new bank account
		case DIALOG_BANK_NEWACCOUNT:
		{
			ShowMsgBox(playerID, dialogID, LanguageString(playerID, 210), LanguageString(playerID, 211), MSGBOXSTYLE_YESNO);
		}
		// Withdraw money from the bank account
		case DIALOG_BANK_WITHDRAWMONEY:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, LanguageString(playerID, 207), LanguageString(playerID, 213), "OK", LanguageString(playerID, 165));
		}
		case DIALOG_BUYHOUSE:
		{
			new string[70];
			GetStringArg(2, string);
			Format:string("Dieses Haus kann noch gekauft werden.\n\nPreis: $%s", string);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_MSGBOX, "Haus kaufen", string, "Kaufen", LanguageString(playerID, 165));
		}
		case DIALOG_BUYVEHICLE:
		{
			new string[70];
			GetStringArg(2, string);
			Format:string("Möchtest du dieses Fahrzeug Kaufen?\n\nPreis: $%s", string);
			ShowMsgBox(playerID, dialogID, "Fahrzeug kaufen", string, MSGBOXSTYLE_YESNO);
		}
		case DIALOG_ESTATEAGENTS:
		{
			FormatNew:options[50]("%s\n%s", LanguageString(playerID, 217), LanguageString(playerID, 218));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 222), options, LanguageString(playerID, 177), LanguageString(playerID, 165));
		}
		case DIALOG_CHANGEPASSWORD_STEP1:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Accountpasswort ändern", "Gebe dein aktuelles Passwort ein.", "Weiter", LanguageString(playerID, 165));
		}
		case DIALOG_CHANGEPASSWORD_STEP2:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Accountpasswort ändern", "Gebe ein neues Passwort ein.", "Weiter", "Zurück");
		}
		case DIALOG_CHANGEPASSWORD_STEP3:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Accountpasswort ändern", "Wiederhole zur Sicherheit dein neues Passwort.", "OK", "Zurück");
		}
		case DIALOG_FUNACTION:
		{
			FormatNew:string[1024]("Animation/Aktion stoppen\n");
			Format:string("%s\nDance 1\nDance 2\nDance 3\nDance 4", string);
			Format:string("%s\nHands Up\nSitting", string);
			Format:string("%s\nDrink Beer\nSmoke Ciggy\nDrink Wine\nDrink Sprunk", string);
			Format:string("%s\nPissing", string);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Fun Action", string, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_HOTEL_MAIN_AVAILABLE:
		{
			FormatNew:options[40]("Hotel kaufen"); // Item 0
			Format:options("%s\nZimmer mieten", options); // Item 1
			Format:options("%s\nBetreten", options); // Item 2
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hotel", options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_HOTEL_MAIN_BOUGHT:
		{
			FormatNew:options[30]("Betreten"); // Item 0
			Format:options("%s\nMieten", options); // Item 1
			Format:options("%s\nKündigen", options); // item 2
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hoteloptionen", options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_HOTEL_MAIN_OWNER:
		{
			FormatNew:options[50]("Betreten"); // Item 0
			Format:options("%s\nVerkaufen", options); // Item 1
			Format:options("%s\nEinnahmen", options); // item 2
			Format:options("%s\nZimmeroptionen", options); // Item 3
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hoteloptionen", options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_HOTEL_ROOMS_FREEOPTIONS:
		{
			FormatNew:options[20]("Mietpreis festlegen"); // Item 0
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Zimmeroptionen", options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_HOTEL_ROOMS_LIST:
		{
			new rooms[2048];
			new string[MAX_PLAYER_NAME];
			MySQLQuery("SELECT `RoomID`, `Username` FROM `hotelrooms` LEFT JOIN `users` ON `hotelrooms`.`OwnerUserID` = `users`.`ID` WHERE `hotelrooms`.`BuildingID` = '%d' ORDER BY `RoomID` ASC", PVar:playerID[DIALOGBUILDINGID]);
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
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Zimmer wählen", rooms, "Optionen", LanguageString(playerID, 165));
		}
		case DIALOG_HOTEL_ROOMS_OWNEDOPTIONS:
		{
			new options[20];
			Format:options("Mieter rauswerfen", options); // Item 0
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Zimmeroptionen", options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_HOUSEOPTIONS:
		{
			FormatNew:options[20]("Betreten");// Item 0
			Format:options("%s\nVerkaufen", options);// Item 1
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Hausoptionen", options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_LOGIN:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Login", "Bitte gebe das Passwort von deinen Account ein.", "OK", LanguageString(playerID, 165));
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
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Fahrzeug bestellen", vehicleList, "Bestellen", LanguageString(playerID, 165));
		}
		case DIALOG_PAYDAYINFO:
		{
			new difference = GetOnlineTime(playerID) - PVar:playerID[LASTPAYDAY];
			MySQLQuery("SELECT * FROM `moneytransactions` WHERE `UserID` = '%d' AND `Type` = '%s'", PVar:playerID[USERID], CASHTRANS_PAYDAY);
			mysql_store_result();
			new Float:amount = floatstr(GetMySQLField("Amount"));
			mysql_free_result();
			FormatNew:string[160]("Letztes Nettoeinkommen:\t\t\t$%s", FormatMoney(amount));
			Format:string("%s\n\nVergangene Zeit seit dem letzten Zahltag:\t%s", string, FormatTime(difference));
			Format:string("%s\n\nZeit bis zum nächsten Zahltag:\t\t\t%s", string, FormatTime(PAYDAY_INTERVAL - difference));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_MSGBOX, "Informationen über den Zahltag", string, "OK", "");
		}
		case DIALOG_POLICE:
		{
			FormatNew:options[10]("Betreten");
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Polizei", options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_POLICE_JOB:
		{
			FormatNew:options[60]("Polizeirevier kaufen");
			Format:options("%s\nBewerben", options);
			Format:options("%s\nBetreten", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Polizei", options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_POLICE_OPTIONS:
		{
			FormatNew:options[70]("Aufträge");
			Format:options("%s\nFinazen", options);
			Format:options("%s\nBewerbungsübersicht", options);
			Format:options("%s\nKündigen", options);
			Format:options("%s\nBetreten", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Polizei", options, "OK", LanguageString(playerID, 165));
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
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Radiosender wählen", stations, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_REFUEL:
		{
			new string[80];
			GetStringArg(2, string);
			PVar:playerID[CURRENTGASPRICE] = gasPrice;
			Format:string("Wie viel möchtest du tanken (0 - %s)?\n\nAktueller Preis: $%s/Liter", string, FormatMoney(gasPrice));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, "Tanken", string, "Tanken", LanguageString(playerID, 165));
		}
		case DIALOG_REGISTER_BIRTHDATE:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, "Geburtsdatum eingeben", "Gebe dein Geburtsdatum im Format TT.MM.JJJJ ein.\n\nBeispiel: 05.02.1990", "Weiter", "Zurück");
		}
		case DIALOG_REGISTER_GENDER:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Geschlecht auswählen", "Männlich\nWeiblich", "Weiter", "Zurück");
		}
		case DIALOG_REGISTER_LOCATION:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, "Wohnort eingeben", "Gebe deinen Wohnort ein.\n\nHinweis: Kann auch ein Wohnort in San Andreas sein.", "OK", "Zurück");
		}
		case DIALOG_REGISTER_PASSWORD1:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Registrieren", "Du bist noch nicht registriert!\nBitte gebe ein neues Passwort für deinen Account ein.", "Weiter", LanguageString(playerID, 165));
		}
		case DIALOG_REGISTER_PASSWORD2:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Passwort wiederholen", "Wiederhole zur Sicherheit dein neues Passwort.", "Weiter", "Zurück");
		}
		case DIALOG_RESTARTGAMEMODE:
		{
			ShowMsgBox(playerID, dialogID, "Gamemode neustarten", "Soll der Gamemode wirklich neugestartet werden?", MSGBOXSTYLE_YESNO);
		}
		case DIALOG_SCHOOLDRIVER:
		{
			FormatNew:options[50]("%s\n%s", LanguageString(playerID, 217), LanguageString(playerID, 218));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 223), options, LanguageString(playerID, 177), LanguageString(playerID, 165));
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
			PVar:playerID[INTERIORDIALOGID] = getarg(2);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, string, interiors, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_STATS:
		{
			new string[1024];
			SavePlayer(playerID);
			Format:string("SELECT `users`.`ID`, `users`.`Username`, UNIX_TIMESTAMP(`users`.`BirthDate`) AS `BirthDate`, `users`.`Location`, `users`.`MobilePhoneNumber`, `users`.`BankID`, `users`.`BankMoney`, `users`.`CreditMoney`, `users`.`JobID`, `users`.`OnlineTime`, `users`.`RegisterTime`, `users`.`LoginTime`, `banks`.`Name` AS `Bank`, `jobs`.`Name` AS `JobName` FROM `users`");
			MySQLQuery("%s LEFT JOIN (`banks`, `jobs`) ON (`banks`.`ID` = `users`.`BankID` AND `jobs`.`ID` = `users`.`JobID`) WHERE `users`.`ID` = '%d'", string, PVar:playerID[USERID]);
			mysql_store_result();
			Format:string("ID:\t\t\t%s", GetMySQLField("ID"));
			Format:string("%s\nName:\t\t\t%s", string, GetMySQLField("Username"));
			Format:string("%s\nAlter:\t\t\t%d Jahre", string, CalculateAge(strval(GetMySQLField("BirthDate"))));
			Format:string("%s\nWohnort:\t\t%s", string, GetMySQLField("Location"));
			Format:string("%s\nHandynummer:\t\t%s", string, GetMySQLField("MobilePhoneNumber"));
			if (strval(GetMySQLField("BankID")))
			{
				Format:string("%s\nBank:\t\t%s", string, GetMySQLField("Bank"));
				Format:string("%s\nGuthaben (Bank):\t\t%s", string, FormatMoney(floatstr(GetMySQLField("BankMoney"))));
				Format:string("%s\nGuthaben (Kreditkarte):\t\t%s", string, FormatMoney(floatstr(GetMySQLField("CreditMoney"))));
			}
			Format:string("%s\nGuthaben:\t\t$%s", string, FormatMoney(PVar:playerID[MONEY]));
			if (strval(GetMySQLField("JobID")))
			{
				Format:string("%s\nBeruf:\t\t\t%s", string, GetMySQLField("JobName"));
			}
			Format:string("%s\nSpielzeit:\t\t%s", string, FormatTime(strval(GetMySQLField("OnlineTime"))));
			Format:string("%s\nRegistriert seit:\t\t%s", string, FormatDate(GetMySQLField("RegisterTime")));
			Format:string("%s\nLetzter Login:\t\t%s", string, FormatDate(GetMySQLField("LoginTime")));
			mysql_free_result();
			ShowMsgBox(playerID, dialogID, "Personalien", string);
		}
		case DIALOG_TAXI:
		{
			FormatNew:options[50]("%s\n%s", LanguageString(playerID, 217), LanguageString(playerID, 218));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 224), options, LanguageString(playerID, 177), LanguageString(playerID, 165));
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
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Teleportieren", locations, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_TRUCKER_JOB:
		{
			FormatNew:options[30]("Truckerfirma kaufen");
			Format:options("%s\nBewerben", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Trucker", options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_TRUCKER_OPTIONS:
		{
			FormatNew:options[50]("Aufträge");
			Format:options("%s\nFinanzen", options);
			Format:options("%s\nKündigen", options);
			Format:options("%s\nBewerbungsübersicht", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Trucker Übersicht", options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_VEHICLEDEALER_JOB:
		{
			new options[50];
			Format:options("Autohändler kaufen");
			Format:options("%s\nBewerben", options);
			Format:options("%s\nFahrzeug Kaufen", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Autohändler", options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_VEHICLEDEALER_OPTIONS:
		{
			new options[70];
			Format:options("Fahrzeug bestellen");
			Format:options("%s\nFinanzen", options);
			Format:options("%s\nKündigen", options);
			Format:options("%s\nBewerbungsübersicht", options);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Autohändlerübersicht", options, "OK", LanguageString(playerID, 165));
		}
	}
}