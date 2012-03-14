Timer:Fast()
{
	PlayerLoop(playerID)
	{
		if (IsLoggedIn(playerID))
		{
			new onlineTime = GetOnlineTime(playerID);
			if (onlineTime - PVar:playerID[LASTPAYDAY] >= PAYDAY_INTERVAL)
			{
				PVar:playerID[LASTPAYDAY] = onlineTime;
				PVar:playerID[PAYDAY] = true;
			}
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