ShowDialog(playerID, dialogID, {_, Float, Text3D, Menu, Text, DB, DBResult, bool, File, hex, bit, bit_byte, Bit}:...)
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
		case DIALOG_ARMY:
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
			Format:string(LanguageString(playerID, 235), string);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_MSGBOX, LanguageString(playerID, 236), string, LanguageString(playerID, 237), LanguageString(playerID, 165));
		}
		case DIALOG_BUYVEHICLE:
		{
			new string[70];
			GetStringArg(2, string);
			Format:string(LanguageString(playerID, 244), string);
			ShowMsgBox(playerID, dialogID, LanguageString(playerID, 245), string, MSGBOXSTYLE_YESNO);
		}
		case DIALOG_ESTATEAGENTS:
		{
			FormatNew:options[50]("%s\n%s", LanguageString(playerID, 217), LanguageString(playerID, 218));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 222), options, LanguageString(playerID, 177), LanguageString(playerID, 165));
		}
		case DIALOG_CHANGEPASSWORD_STEP1:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, LanguageString(playerID, 240), LanguageString(playerID, 241), LanguageString(playerID, 177), LanguageString(playerID, 165));
		}
		case DIALOG_CHANGEPASSWORD_STEP2:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, LanguageString(playerID, 240), LanguageString(playerID, 242), LanguageString(playerID, 177), LanguageString(playerID, 171));
		}
		case DIALOG_CHANGEPASSWORD_STEP3:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, LanguageString(playerID, 240), LanguageString(playerID, 243), "OK", LanguageString(playerID, 171));
		}
		case DIALOG_CHATMODE:
		{
			new options[1024];
			AddLine(options, LanguageString(playerID, 311));// Item 0
			AddLine(options, LanguageString(playerID, 310));// Item 1
			AddLine(options, "Job");// Item 2
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 312), options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_FUNACTION:
		{
			FormatNew:string[1024]("Stop\n");
			Format:string("%s\nDance 1\nDance 2\nDance 3\nDance 4", string);
			Format:string("%s\nHands Up\nSitting", string);
			Format:string("%s\nDrink Beer\nSmoke Ciggy\nDrink Wine\nDrink Sprunk", string);
			Format:string("%s\nPissing", string);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, "Fun Action", string, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_HOTEL_HASROOM:
		{
			new options[1024];
			AddLine(options, LanguageString(playerID, 317));// Item 0
			AddLine(options, LanguageString(playerID, 318));// Item 1
			AddLine(options, LanguageString(playerID, 319));// Item 2
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 316), options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_HOTEL_ROOMLIST:
		{
			new rooms[2048];
			GetStringArg(2, rooms);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 315), rooms, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_HOUSE:
		{
			new options[1024];
			AddLine(options, LanguageString(playerID, 268));// Item 0
			AddLine(options, LanguageString(playerID, 328));// Item 1
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 329), options, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_LOGIN:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, "Login", LanguageString(playerID, 262), "OK", LanguageString(playerID, 165));
		}
		case DIALOG_NAVITARGET:
		{
			new targets[1024];
			AddLine(targets, LanguageString(playerID, 173));// Item 0 (Bank)
			AddLine(targets, LanguageString(playerID, 174));// Item 1 (Hotel)
			AddLine(targets, LanguageString(playerID, 175));// Item 2 (House)
			AddLine(targets, LanguageString(playerID, 342));// Item 3 (Target on map)
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 247), targets, LanguageString(playerID, 341), LanguageString(playerID, 165));
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
		case DIALOG_PREVIEWINFO:
		{
			ShowMsgBox(playerID, dialogID, LanguageString(playerID, 269), LanguageString(playerID, 270));
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
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 252), stations, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_REFUEL:
		{
			new string[80];
			GetStringArg(2, string);
			PVar:playerID[CURRENTGASPRICE] = gasPrice;
			Format:string(LanguageString(playerID, 238), string, FormatMoney(gasPrice));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, LanguageString(playerID, 239), string, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_REGISTER_BIRTHDATE:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, LanguageString(playerID, 253), LanguageString(playerID, 254), LanguageString(playerID, 177), LanguageString(playerID, 171));
		}
		case DIALOG_REGISTER_GENDER:
		{
			FormatNew:options[50]("%s\n%s", LanguageString(playerID, 256), LanguageString(playerID, 257));
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 255), options, LanguageString(playerID, 177), LanguageString(playerID, 171));
		}
		case DIALOG_REGISTER_LOCATION:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_INPUT, LanguageString(playerID, 258), LanguageString(playerID, 259), "OK", LanguageString(playerID, 171));
		}
		case DIALOG_REGISTER_PASSWORD1:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, LanguageString(playerID, 260), LanguageString(playerID, 261), LanguageString(playerID, 177), LanguageString(playerID, 165));
		}
		case DIALOG_REGISTER_PASSWORD2:
		{
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_PASSWORD, LanguageString(playerID, 251), LanguageString(playerID, 243), LanguageString(playerID, 177), LanguageString(playerID, 171));
		}
		case DIALOG_REPAIR:
		{
			FormatNew:string[100](LanguageString(playerID, 302), GetPlayerNameEx(PVar:playerID[REPAIR_EXECUTOR]), FormatMoney(PVar:playerID[REPAIR_PRICE]));
			ShowMsgBox(playerID, dialogID, LanguageString(playerID, 301), string, MSGBOXSTYLE_YESNO);
		}
		case DIALOG_RESTARTGAMEMODE:
		{
			ShowMsgBox(playerID, dialogID, LanguageString(playerID, 249), LanguageString(playerID, 250), MSGBOXSTYLE_YESNO);
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
					Format:interiors("%s\n%s", interiors, LanguageString(playerID, 177));
				}
				case 2:
				{
					Format:interiors("%s\n%s", interiors, LanguageString(playerID, 177));
				}
			}
			FormatNew:string[30]("%s (%s %d)", LanguageString(playerID, 247), LanguageString(playerID, 248), page);
			PVar:playerID[INTERIORDIALOGID] = getarg(2);
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, string, interiors, "OK", LanguageString(playerID, 165));
		}
		case DIALOG_STATS:
		{
			new string[1024];
			SavePlayer(playerID);
			Format:sqlQuery("SELECT `users`.`ID`, `users`.`Username`, UNIX_TIMESTAMP(`users`.`BirthDate`) AS `BirthDate`, `users`.`Location`, `users`.`MobilePhoneNumber`, `users`.`BankID`, `users`.`BankMoney`, `users`.`JobID`, `users`.`OnlineTime`, `users`.`RegisterTime`, `users`.`LoginTime`, `banks`.`Name` AS `Bank`, `jobs`.`Name` AS `JobName` FROM `users`");
			MySQLQuery("%s LEFT JOIN (`banks`, `jobs`) ON (`banks`.`ID` = `users`.`BankID` AND `jobs`.`ID` = `users`.`JobID`) WHERE `users`.`ID` = '%d'", sqlQuery, PVar:playerID[USERID]);
			mysql_store_result();
			Format:string("ID: %s", GetMySQLField("ID"));
			Format:string("%s\nName: %s", string, GetMySQLField("Username"));
			Format:string("%s\n%s: %d %s", string, LanguageString(playerID, 226), CalculateAge(strval(GetMySQLField("BirthDate"))), LanguageString(playerID, 307));
			Format:string("%s\n%s: %s", string, LanguageString(playerID, 227), GetMySQLField("Location"));
			Format:string("%s\n%s: %s", string, LanguageString(playerID, 228), GetMySQLField("MobilePhoneNumber"));
			if (strval(GetMySQLField("BankID")))
			{
				Format:string("%s\nBank: %s", string, GetMySQLField("Bank"));
				Format:string("%s\n%s (Bank): %s", string, LanguageString(playerID, 229), FormatMoney(floatstr(GetMySQLField("BankMoney"))));
			}
			Format:string("%s\n%s: $%s", string, LanguageString(playerID, 229), FormatMoney(PVar:playerID[MONEY]));
			if (strval(GetMySQLField("JobID")))
			{
				Format:string("%s\n%s: %s", string, LanguageString(playerID, 230), GetMySQLField("JobName"));
			}
			Format:string("%s\n%s: %s", string, LanguageString(playerID, 231), FormatTime(strval(GetMySQLField("OnlineTime"))));
			Format:string("%s\n%s: %s", string, LanguageString(playerID, 232), FormatDate(GetMySQLField("RegisterTime")));
			Format:string("%s\n%s: %s", string, LanguageString(playerID, 233), FormatDate(GetMySQLField("LoginTime")));
			mysql_free_result();
			ShowMsgBox(playerID, dialogID, LanguageString(playerID, 234), string);
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
			ShowPlayerDialog(playerID, dialogID, DIALOG_STYLE_LIST, LanguageString(playerID, 246), locations, "OK", LanguageString(playerID, 165));
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