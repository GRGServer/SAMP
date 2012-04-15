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
				PayDay(playerID);
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
				new Float:distance;
				new Float:healthPercentage;
				new Float:fuelPercentage;
				new vehicleID = GetPlayerVehicleID(playerID);
				new vehicleModelIndex = GetVehicleModel(vehicleID) - 400;
				GetVehicleVelocity(vehicleID, velocityX, velocityY, velocityZ);
				GetVehicleHealth(vehicleID, health);
				speed = floatround(floatsqroot(floatpower(velocityX, 2) + floatpower(velocityY, 2) + floatpower(velocityZ, 2)) * 100 * 1.61);
				distance = floatdiv(speed, floatdiv(1000 * 60 * 60, TIMER_FAST));
				vehicles[vehicleID][VEHICLE_MILEAGE] = floatadd(vehicles[vehicleID][VEHICLE_MILEAGE], distance);
				healthPercentage = floatdiv(health, 10);
				if (vehicles[vehicleID][VEHICLE_CURRENTFUEL] <= 0)
				{
					SetVehicleEngineState(vehicleID, false);
					GameTextForPlayer(playerID, LanguageString(playerID, 159), 3000, 5);
				}
				else
				{
					vehicles[vehicleID][VEHICLE_CURRENTFUEL] = floatsub(vehicles[vehicleID][VEHICLE_CURRENTFUEL], distance * floatdiv(vehicleModels[vehicleModelIndex][VEHICLEMODEL_FUELUSAGE], 100));
				}
				fuelPercentage = floatmul(floatdiv(vehicles[vehicleID][VEHICLE_CURRENTFUEL], vehicleModels[vehicleModelIndex][VEHICLEMODEL_MAXFUEL]), 100);
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
						GameTextForPlayer(playerID, LanguageString(playerID, 158), 3000, 5);
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
				FormatNew:textDrawString[60]("~n~%d Km/h~n~~%c~%s%%~w~~n~~%c~%s%%~w~~n~%sl~n~%s", speed, healthColor, FormatNumber(healthPercentage, 2, '.', ','), fuelColor, FormatNumber(fuelPercentage, 2, '.', ','), FormatNumber(vehicleModels[vehicleModelIndex][VEHICLEMODEL_FUELUSAGE], 1, '.', ','), FormatNumber(vehicles[vehicleID][VEHICLE_MILEAGE], 2, '.', ','));
				PlayerTextDrawSetString(playerID, PTextDraw:playerID[SPEEDO_COLUMN2], textDrawString);
				PlayerTextDrawSetString(playerID, PTextDraw:playerID[VEHICLENAME], vehicleModels[vehicleModelIndex][VEHICLEMODEL_NAME]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[SPEEDO_COLUMN1]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[SPEEDO_COLUMN2]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[VEHICLENAME]);
			}
			else
			{
				PlayerTextDrawHide(playerID, PTextDraw:playerID[SPEEDO_COLUMN1]);
				PlayerTextDrawHide(playerID, PTextDraw:playerID[SPEEDO_COLUMN2]);
				PlayerTextDrawHide(playerID, PTextDraw:playerID[VEHICLENAME]);
			}
		}
	}
}