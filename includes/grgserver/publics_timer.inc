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
				GetVehicleVelocity(vehicleID, velocityX, velocityY, velocityZ);
				GetVehicleHealth(vehicleID, health);
				speed = floatround(floatsqroot(floatabs(floatpower(velocityX + velocityY + velocityZ, 2))) * 100 * 1.61);
				healthPercentage = floatround(health /10);
				fuelPercentage = floatround((vehicles[vehicleID][vehicles_currentFuel] / vehicleModels[GetVehicleModel(vehicleID) - 400][vehicleModels_maxFuel]) * 100);
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
						if (healthPercentage < 30)
						{
							if (GetVehicleEngineState(vehicleID))
							{
								SetVehicleEngineState(vehicleID, false);
								GameTextForPlayer(playerID, "Dein Fahrzeug ist kaputt!", 3000, 6);
							}
						}
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
				if (vehicles[vehicleID][vehicles_currentFuel] <= 0)
				{
					SetVehicleEngineState(vehicleID, false);
					GameTextForPlayer(playerID, "Der Tank von deinem fahrzeug ist leer!", 3000, 6);
				}
				format(string, sizeof(string), "Geschwindigkeit: %d Km/h~n~Zustand: ~%c~%d%%~w~~n~Tank: ~%c~%d%%~w~", speed, healthColor, healthPercentage, fuelColor, fuelPercentage);
				TextDrawSetString(textDrawSpeedo[playerID], string);
				TextDrawShowForPlayer(playerID, textDrawSpeedo[playerID]);
			}
			else
			{
				TextDrawHideForPlayer(playerID, textDrawSpeedo[playerID]);
			}
		}
	}
}

forward timer_slow();
public timer_slow()
{
	new hour;
	new minute;
	new second;
	gettime(hour, minute, second);
	SetWorldTime(hour);
	mysql_ping();
}
