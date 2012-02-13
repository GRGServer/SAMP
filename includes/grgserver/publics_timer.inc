forward timer_fast();
public timer_fast()
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID))
		{
			if (IsPlayerInAnyVehicle(playerID))
			{
				new Float:velocityX;
				new Float:velocityY;
				new Float:velocityZ;
				new Float:health;
				new string[256];
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
				if (vehicles[vehicleID][vehicles_currentFuel] <= 0)
				{
					SetVehicleEngineState(vehicleID, false);
					GameTextForPlayer(playerID, "Der Tank von deinem Fahrzeug ist leer!", 3000, 5);
				}
				else
				{
					vehicles[vehicleID][vehicles_currentFuel] = floatsub(vehicles[vehicleID][vehicles_currentFuel], floatdiv(speed, 60 * 60 * 4) * floatdiv(vehicleModels[vehicleModelIndex][vehicleModels_fuelUsage], 100));
				}
				fuelPercentage = floatround((vehicles[vehicleID][vehicles_currentFuel] / vehicleModels[vehicleModelIndex][vehicleModels_maxFuel]) * 100);
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
				format(string, sizeof(string), "%d Km/h~n~~%c~%d%%~w~~n~~%c~%d%%~w~~n~%fl", speed, healthColor, healthPercentage, fuelColor, fuelPercentage, vehicleModels[vehicleModelIndex][vehicleModels_fuelUsage]);
				TextDrawSetString(textDrawSpeedoColumn2[playerID], string);
				TextDrawShowForPlayer(playerID, textDrawSpeedoColumn1);
				TextDrawShowForPlayer(playerID, textDrawSpeedoColumn2[playerID]);
			}
			else
			{
				TextDrawHideForPlayer(playerID, textDrawSpeedoColumn1);
				TextDrawHideForPlayer(playerID, textDrawSpeedoColumn2[playerID]);
			}
		}
	}
}

forward timer_slow();
public timer_slow()
{
	new clockString[6];
	new hourString[3];
	new minuteString[3];
	new hour;
	new minute;
	new second;
	gettime(hour, minute, second);
	format(hourString, sizeof(hourString), "%2d", hour);
	format(minuteString, sizeof(minuteString), "%2d", minute);
	if (hour < 10)
	{
		hourString[0] = '0';
	}
	if (minute < 10)
	{
		minuteString[0] = '0';
	}
	format(clockString, sizeof(clockString), "%s:%s", hourString, minuteString);
	TextDrawSetString(textDrawClock, clockString);
	SetWorldTime(hour);
	mysql_ping();
}

forward timer_hourly();
public timer_hourly()
{
	UpdateGasPrice();
}

forward timer_refuelVehicle(playerID, Float:amount);
public timer_refuelVehicle(playerID, Float:amount)
{
	new vehicleID = GetPlayerVehicleID(playerID);
	if (GetPVarFloat(playerID, "Money") >= gasPrice)
	{
		new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][vehicleModels_maxFuel], vehicles[vehicleID][vehicles_currentFuel]);
		if (amount > 0)
		{
			if (maximum < 1)
			{
				vehicles[vehicleID][vehicles_currentFuel] = floatadd(vehicles[vehicleID][vehicles_currentFuel], maximum);
				GivePlayerMoneyEx(playerID, -(gasPrice * maximum));
			}
			else
			{
				vehicles[vehicleID][vehicles_currentFuel] = floatadd(vehicles[vehicleID][vehicles_currentFuel], 1.0);
				GivePlayerMoneyEx(playerID, -gasPrice);
				SetTimerEx("timer_refuelVehicle", GASSTATION_REFUELSPEED, false, "df", playerID, floatsub(amount, 1.0));
				return true;
			}
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