Timer:EveryMinute()
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		savePlayers[playerID] = IsLoggedIn(playerID);
	}
}

Timer:Fast()
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID))
		{
			if (IsPlayerInAnyVehicle(playerID) && GetPlayerVehicleSeat(playerID) == 0)
			{
				new Float:velocityX;
				new Float:velocityY;
				new Float:velocityZ;
				new Float:health;
				new healthColor;
				new fuelColor;
				new speed;
				new healthPercentage;
				new fuelPercentage;
				new vehicleID = GetPlayerVehicleID(playerID);
				new vehicleModelIndex = GetVehicleModel(vehicleID) - 400;
				GetVehicleVelocity(vehicleID, velocityX, velocityY, velocityZ);
				GetVehicleHealth(vehicleID, health);
				speed = floatround(floatsqroot(floatabs(floatpower(velocityX + velocityY + velocityZ, 2))) * 100 * 1.61);
				healthPercentage = floatround(health /10);
				if (vehicles[vehicleID][VEHICLE_CURRENTFUEL] <= 0)
				{
					SetVehicleEngineState(vehicleID, false);
					GameTextForPlayer(playerID, "Der Tank von deinem Fahrzeug ist leer!", 3000, 5);
				}
				else
				{
					vehicles[vehicleID][VEHICLE_CURRENTFUEL] = floatsub(vehicles[vehicleID][VEHICLE_CURRENTFUEL], floatdiv(speed, 60 * 60 * 4) * floatdiv(vehicleModels[vehicleModelIndex][VEHICLEMODEL_FUELUSAGE], 100));
				}
				fuelPercentage = floatround((vehicles[vehicleID][VEHICLE_CURRENTFUEL] / vehicleModels[vehicleModelIndex][VEHICLEMODEL_MAXFUEL]) * 100);
				if (healthPercentage > 65)
				{
					healthColor = 'g';
				}
				else
				{
					if (healthPercentage > 40)
					{
						healthColor = 'y';
					}
					else
					{
						healthColor = 'r';
					}
				}
				if (healthPercentage <= VEHICLE_MINHEALTH)
				{
					if (GetVehicleEngineState(vehicleID))
					{
						SetVehicleHealth(vehicleID, float(VEHICLE_MINHEALTH * 10));
						SetVehicleEngineState(vehicleID, false);
						GameTextForPlayer(playerID, "Dein Fahrzeug ist kaputt!", 3000, 5);
					}
				}
				if (fuelPercentage > 70)
				{
					fuelColor = 'g';
				}
				else
				{
					if (fuelPercentage > 30)
					{
						fuelColor = 'y';
					}
					else
					{
						fuelColor = 'r';
					}
				}
				FormatNew:textDrawString[60]("~n~%d Km/h~n~~%c~%d%%~w~~n~~%c~%d%%~w~~n~%sl", speed, healthColor, healthPercentage, fuelColor, fuelPercentage, FormatNumber(vehicleModels[vehicleModelIndex][VEHICLEMODEL_FUELUSAGE], 1, '.', ','));
				TextDrawSetString(textDrawSpeedoName[playerID], vehicleModels[vehicleModelIndex][VEHICLEMODEL_NAME]);
				TextDrawSetString(textDrawSpeedoColumn2[playerID], textDrawString);
				TextDrawShowForPlayer(playerID, textDrawSpeedoName[playerID]);
				TextDrawShowForPlayer(playerID, textDrawSpeedoColumn1);
				TextDrawShowForPlayer(playerID, textDrawSpeedoColumn2[playerID]);
			}
			else
			{
				TextDrawHideForPlayer(playerID, textDrawSpeedoName[playerID]);
				TextDrawHideForPlayer(playerID, textDrawSpeedoColumn1);
				TextDrawHideForPlayer(playerID, textDrawSpeedoColumn2[playerID]);
			}
		}
	}
}

Timer:FlyWithPlane(playerID, part)
{
	switch (part)
	{
		case 1:
		{
			// TODO: Fade to black
			GameTextForPlayer(playerID, "7 Stunden später...", 3000, 1);
			SetTimerEx("Timer_FlyWithPlane", 3000, false, "ii", playerID, 2);
		}
		case 2:
		{
			// TODO: Fade back to game
			TogglePlayerControllable(playerID, true);
			SetPlayerCheckpointEx(playerID, CHECKPOINT_WALKTOPLANEEXIT);
		}
	}
}

Timer:Hourly()
{
	UpdateGasPrice();
}

Timer:RefuelVehicle(playerID, Float:totalAmount)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (GetPlayerMoneyEx(playerID) >= GetPVarFloat(playerID, "CurrentGasPrice"))
	{
		new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][VEHICLEMODEL_MAXFUEL], vehicles[vehicleID][VEHICLE_CURRENTFUEL]);
		if (totalAmount > 0 && maximum > 0)
		{
			new Float:amount;
			if (maximum < 1)
			{
				amount = maximum;
			}
			else
			{
				amount = 1.0;
			}
			vehicles[vehicleID][VEHICLE_CURRENTFUEL] = floatadd(vehicles[vehicleID][VEHICLE_CURRENTFUEL], amount);
			GivePlayerMoneyEx(playerID, -floatmul(GetPVarFloat(playerID, "CurrentGasPrice"), amount));
			SetTimerEx("Timer_RefuelVehicle", GASSTATION_REFUELSPEED, false, "df", playerID, floatsub(totalAmount, amount));
			return true;
		}
		SendClientMessage(playerID, COLOR_INFO, "Dein Fahrzeug wurde getankt.");
	}
	else
	{
		SendClientMessage(playerID, COLOR_ERROR, "Du hast nicht genügend Geld!");
	}
	TogglePlayerControllable(playerID, true);
	return true;
}

Timer:Slow()
{
	new hour;
	new minute;
	new second;
	gettime(hour, minute, second);
	FormatNew:hourString[3]("%2d", hour);
	FormatNew:minuteString[3]("%2d", minute);
	if (hour < 10)
	{
		hourString[0] = '0';
	}
	if (minute < 10)
	{
		minuteString[0] = '0';
	}
	FormatNew:clockString[6]("%s:%s", hourString, minuteString);
	TextDrawSetString(textDrawClock, clockString);
	SetWorldTime(hour);
	mysql_ping();
	if (fexist("svn_changes"))
	{
		print("svn_changes file found");
		new string[256];
		new File:file = fopen("svn_changes", io_read);
		fread(file, string);// Skip "------------------------------------------------------------------------"
		fread(file, string);// Read "rXXX | user | yyyy-mm-dd hh:ii:ss +xxxx (ddd, dd mmm yyyy) | x line(s)"
		printf("Read info line: %s", string);
		new revisionString[10];
		new committerName[100];
		new commitDate[50];
		new lineCount[20];
		sscanf(string, "p|ssss", revisionString, committerName, commitDate, lineCount);
		printf("Parsed line and got: rev %s, comitter %s, date %s, lines %s", revisionString, committerName, commitDate, lineCount);
		new revision = strval(revisionString);
		printf("Converted to number: %d", revision);
		if (revision > COMPILER_SVN_REVISION)
		{
			printf("Detected update to revision %d", revision);
			Format:string("Es steht ein Update auf Revision %d zur Verfügung!", revision);
			SendClientMessageToAdmins(PERMISSION_SERVERADMIN, COLOR_SYSTEM, string);
			Format:string("Committer: %s", committerName);
			SendClientMessageToAdmins(PERMISSION_SERVERADMIN, COLOR_SYSTEM, string);
			fread(file, string);// Skip ""
			SendClientMessageToAdmins(PERMISSION_SERVERADMIN, COLOR_SYSTEM, "*** SVN Changelog:");
			while (fread(file, string))
			{
				RemoveNewLine(string);
				if (strlen(string) && strcmp(string, "------------------------------------------------------------------------"))
				{
					Format:string("> %s", string);
					SendClientMessageToAdmins(PERMISSION_SERVERADMIN, COLOR_SYSTEM, string);
				}
			}
		}
		fclose(file);
		fremove("svn_changes");
	}
}

Timer:SpawnPlayer(playerID)
{
	SpawnPlayer(playerID);
	SetPlayerPos(playerID, floatstr(GetUserDBValue(playerID, "PosX")), floatstr(GetUserDBValue(playerID, "PosY")), floatstr(GetUserDBValue(playerID, "PosZ")));
}

Timer:StableCheck()
{
	new File:file = fopen("stable_revision", io_write);
	fwrite(file, val2str(COMPILER_SVN_REVISION));
	fclose(file);
}