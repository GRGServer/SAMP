ShowDialog(playerID, dialogID, ...)
{
	switch (dialogID)
	{
		case DIALOG_ADDBUILDING:
		{
			ShowPlayerDialog(playerID, DIALOG_ADDBUILDING, DIALOG_STYLE_LIST, "Gebäudetyp auswählen", "Bank\nHotel\nHaus", "Weiter", "Abbrechen");
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
			format(query, sizeof(query), "SELECT * FROM `interiors` LIMIT %d,75", startID);
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
			new string[256];
			new query[256];
			new type[256];
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			new pickupID = -1;
			if (interiorID)
			{
				GetPlayerPos(playerID, posX, posY, posZ);
				pickupID = AddPickup(-1, type, posX, posY, posZ, true);
				if (pickupID > 0)
				{
					format(query, sizeof(query), "INSERT INTO `buildings` (`PickupID`, `InteriorID`, `Name`, `Price`) VALUES ('%d', '%s', '%s', '%f')", pickupID, GetMySQLValue("interiors", "ID", "Name", GetPVarStringEx(playerID, "AddBuilding_Interior")), GetPVarStringEx(playerID, "AddBuilding_Name"), GetPVarFloat(playerID, "AddBuilding_Price"));
					mysql_query(query);
					format(string, sizeof(string), "Das Gebäude %s (Preis: %s) wurde mit dem Ziel %s verknüpft und unter der ID %d gespeichert.", GetPVarStringEx(playerID, "AddBuilding_Name"), FormatPrice(GetPVarFloat(playerID, "AddBuilding_Price")), GetPVarStringEx(playerID, "AddBuilding_Interior"), mysql_insert_id());
					SendClientMessage(playerID, COLOR_INFO, string);
				}
				else
				{
					SendClientMessage(playerID, COLOR_ERROR, "Fehler beim Erstellen des Pickups!");
				}
				DeletePVar(playerID, "AddBuilding_Name");
				DeletePVar(playerID, "AddBuilding_Price");
				DeletePVar(playerID, "AddBuilding_Type");
			}
			else
			{
				DeletePVar(playerID, "AddBuilding_Type");
				ShowDialog(playerID, DIALOG_ADDBUILDING);
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