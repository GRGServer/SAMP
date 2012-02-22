ShowDialog(playerID, dialogID, ...)
{
	switch (dialogID)
	{
		case DIALOG_ADDBUILDING_NAME:
		{
			ShowPlayerDialog(playerID, DIALOG_ADDBUILDING_NAME, DIALOG_STYLE_INPUT, "Name eingeben", "Gebe den Name für das Gebäude ein.", "Erstellen", "Zurück");
		}
		case DIALOG_ADDBUILDING_TYPE:
		{
			ShowPlayerDialog(playerID, DIALOG_ADDBUILDING_TYPE, DIALOG_STYLE_LIST, "Gebäudetyp auswählen", "Bank\nHotel\nHaus", "Weiter", "Abbrechen");
		}
		case DIALOG_BUYHOUSE:
		{
			new string[256];
			new price[256];
			GetStringArg(2, price);
			format(string, sizeof(string), "Dieses Haus kann noch gekauft werden.\n\nPreis: %s", price);
			ShowPlayerDialog(playerID, DIALOG_BUYHOUSE, DIALOG_STYLE_MSGBOX, "Haus kaufen", string, "Kaufen", "Abbrechen");
		}
		case DIALOG_BUYVEHICLE:
		{
			new string[256];
			new price[256];
			GetStringArg(2, price);
			format(string, sizeof(string), "Möchtest du dieses Fahrzeug Kaufen?\nDies kostet $%s", price);
			ShowPlayerDialog(playerID, DIALOG_BUYVEHICLE, DIALOG_STYLE_MSGBOX, "Fahrzeug Kaufen", string, "Ja", "Nein");
		}
		case DIALOG_HOTEL:
		{
			new options[1024];
			format(options, sizeof(options), "Hotel Kaufen"); // Item 0
			format(options, sizeof(options), "%s\nZimmer Mieten", options); // Item 1
			format(options, sizeof(options), "%s\nBetreten", options); // Item 2
			ShowPlayerDialog(playerID, DIALOG_HOTEL, DIALOG_STYLE_LIST, "Hotel", options, "OK, "Abbrechen");
		}
		case DIALOG_HOTELOPTIONS:
		{
			new options[1024];
			format(options, sizeof(options), "Betreten"); // Item 0
			format(options, sizeof(options), "%s\nVerkaufen", options); // Item 1
			format(options, sizeof(options), "%s\nEinkomm Information", options); // item 2
			format(options, sizeof(options), "%s\nEinmieter", options); // item 3
			format(options, sizeof(options), "%s\nEinmieter Rausschmeissen", options); // item 4
			format(options, sizeof(options), "%s\nMiet preis Festlegen", options);
			ShowPlayerDialog(playerID, DIALOG_HOTELOPTIONS, DIALOG_STYLE_LIST, "Hoteloptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_HOTELOPTIONS_NOTOWNER:
		{
			new options[1024];
			format(options, sizeof(options), "Betreten"); // Item 0
			format(options, sizeof(options), "%s\nMieten", options); // Item 1
			format(options, sizeof(options), "%s\nMiete Kündigen", options); // item 2
			ShowPlayerDialog(playerID, DIALOG_HOTELOPTIONS_NOTOWNER, DIALOG_STYLE_LIST, "Hoteloptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_HOUSEOPTIONS:
		{
			new options[1024];
			format(options, sizeof(options), "Betreten");// Item 0
			format(options, sizeof(options), "%s\nVerkaufen", options);// Item 1
			ShowPlayerDialog(playerID, DIALOG_HOUSEOPTIONS, DIALOG_STYLE_LIST, "Hausoptionen", options, "OK", "Abbrechen");
		}
		case DIALOG_LOGIN:
		{
			ShowPlayerDialog(playerID, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login", "Bitte gebe das Passwort von deinen Account ein.", "OK", "Abbrechen");
		}
		case DIALOG_ORDERVEHICLE:
		{
			ShowPlayerDialog(playerID, DIALOG_ORDERVEHICLE, DIALOG_STYLE_LIST, "Fahrzeug bestellen", "Landstalker\nBravura\nBuffalo\nLinerunner\nPerenniel\nSentinel\nFiretruck", "Bestellen", "Abbrechen");
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
			ShowPlayerDialog(playerID, DIALOG_RADIO, DIALOG_STYLE_LIST, "Radiosender wählen", stations, "OK", "Abbrechen");
		}
		case DIALOG_REFUEL:
		{
			new string[256];
			new maximum[256];
			GetStringArg(2, maximum);
			format(string, sizeof(string), "Wie viel möchtest du tanken (0 - %s)?", maximum);
			ShowPlayerDialog(playerID, DIALOG_REFUEL, DIALOG_STYLE_INPUT, "Tanken", string, "Tanken", "Abbrechen");
		}
		case DIALOG_REGISTER_STEP1:
		{
			ShowPlayerDialog(playerID, DIALOG_REGISTER_STEP1, DIALOG_STYLE_PASSWORD, "Registrieren", "Du bist noch nicht registriert!\nBitte gebe ein neues Passwort für deinen Account ein.", "OK", "Abbrechen");
		}
		case DIALOG_REGISTER_STEP2:
		{
			ShowPlayerDialog(playerID, DIALOG_REGISTER_STEP2, DIALOG_STYLE_PASSWORD, "Passwort wiederholen", "Gebe erneut das Passwort ein.", "Registrieren", "Zurück");
		}
		case DIALOG_RESTARTGAMEMODE:
		{
			ShowPlayerDialog(playerID, DIALOG_RESTARTGAMEMODE, DIALOG_STYLE_MSGBOX, "Gamemode neustarten", "Soll der Gamemode wirklich neugestartet werden?", "Ja", "Nein");
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
			ShowPlayerDialog(playerID, DIALOG_SELECTINTERIOR, DIALOG_STYLE_LIST, string, interiors, "OK", "Abbrechen");
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
			ShowPlayerDialog(playerID, DIALOG_TELEPORTLOCATIONS, DIALOG_STYLE_LIST, "Teleportieren", locations, "OK", "Abbrechen");
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