/**
 * <summary>
 *	<title>This timer executes the following tasks every 250ms:</title>
 *	<item>Check payday</item>
 *	<item>Call OnPlayerZoneChange if the zone has changed</item>
 *	<item>Update vehicle information</item>
 *	<item>Update vehicle information TextDraw in the bottom right corner</item>
 *	<item>Check speed cameras</item>
 *	<item>Update position in ShowPos TextDraw</item>
 * </summary>
 *
 * <remarks>
 *	Only really fast stuff should be called in this timer!
 *	This means no file operations or database queries should be called directly (If required do a check whether the file operation or database query is really necessary).
 *	See the speed camera check for such a check (Database query in this timer).
 * </remarks>
 */

Timer:Fast()
{
	Count1(vehicleID, MAX_VEHICLES)
	{
		new modelID = GetVehicleModel(vehicleID);
		if (modelID >= 400 && modelID <= 611)
		{
			new Float:velocityX;
			new Float:velocityY;
			new Float:velocityZ;
			new Float:health;
			GetVehicleVelocity(vehicleID, velocityX, velocityY, velocityZ);
			GetVehicleHealth(vehicleID, health);
			VehicleProperty:vehicleID[SPEED] = floatround(floatsqroot(floatpower(velocityX, 2) + floatpower(velocityY, 2) + floatpower(velocityZ, 2)) * 100 * 1.61);
			new Float:distance = floatdiv(VehicleProperty:vehicleID[SPEED], floatdiv(1000 * 60 * 60, TIMER_FAST));
			VehicleProperty:vehicleID[MILEAGE] = floatadd(VehicleProperty:vehicleID[MILEAGE], distance);
			if (GetVehicleEngineState(vehicleID))
			{
				if (VehicleProperty:vehicleID[CURRENTFUEL] <= 0)
				{
					VehicleProperty:vehicleID[CURRENTFUEL] = 0;
					SetVehicleEngineState(vehicleID, false);
				}
				else
				{
					new Float:fuelUsage = distance * floatdiv(vehicleModels[modelID - 400][VEHICLEMODEL_FUELUSAGE], 100);
					if (!VehicleProperty:vehicleID[SPEED])
					{
						fuelUsage = 0.0001;// Fuel usage while engine is idle (Speed is 0 but engine is turned on)
					}
					VehicleProperty:vehicleID[CURRENTFUEL] = floatsub(VehicleProperty:vehicleID[CURRENTFUEL], fuelUsage);
				}
				if (floatdiv(health, 10) <= VEHICLE_MINHEALTH)
				{
					SetVehicleHealth(vehicleID, float(VEHICLE_MINHEALTH * 10));
					SetVehicleEngineState(vehicleID, false);
				}
			}
		}
	}
	Count(playerID, maxPlayers)
	{
		new inVehicle;
		new onlineTime = GetOnlineTime(playerID);
		if (onlineTime - PVar:playerID[LASTPAYDAY] >= PAYDAY_INTERVAL)
		{
			PVar:playerID[LASTPAYDAY] = onlineTime;
			PayDay(playerID);
		}
		new zone = GetPlayerZone(playerID, true);
		if (zone != -1)
		{
			if (PVar:playerID[ZONE] == -1 || (PVar:playerID[ZONE] != zone && !IsStr(zones[PVar:playerID[ZONE]][ZONE_NAME], zones[zone][ZONE_NAME])))
			{
				PVar:playerID[ZONE] = zone;
				OnPlayerZoneChange(playerID, zone);
			}
		}
		if (IsPlayerInAnyVehicle(playerID))
		{
			new vehicleID = GetPlayerVehicleID(playerID);
			new modelID = GetVehicleModel(vehicleID);
			if (modelID >= 400 && modelID <= 611)
			{
				new Float:health;
				new healthColor;
				new fuelColor;
				GetVehicleHealth(vehicleID, health);
				new seatID = GetPlayerVehicleSeat(playerID);
				new Float:distance = floatdiv(VehicleProperty:vehicleID[SPEED], floatdiv(1000 * 60 * 60, TIMER_FAST));
				if (!seatID)
				{
					VehicleProperty:vehicleID[MILEAGE] = floatadd(VehicleProperty:vehicleID[MILEAGE], distance);
				}
				new Float:healthPercentage = floatdiv(health, 10);
				if (health < 1000 && !seatID && IsPlayerNPC(playerID))
				{
					SetVehicleHealth(vehicleID, 1000);
				}
				if (!seatID && VehicleProperty:vehicleID[CURRENTFUEL] <= 0)
				{
					GameTextForPlayer(playerID, LanguageString(playerID, StringID:159("The tank of your vehicle is empty!")), 3000, 5);
				}
				new Float:fuelPercentage = floatmul(floatdiv(VehicleProperty:vehicleID[CURRENTFUEL], vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL]), 100);
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
				if (!seatID && healthPercentage <= VEHICLE_MINHEALTH && GetVehicleEngineState(vehicleID))
				{
					GameTextForPlayer(playerID, LanguageString(playerID, StringID:158("Your vehicle is broken!")), 3000, 5);
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
				FormatNew:textDrawString[60]("~n~%d Km/h~n~~%c~%s%%~w~~n~~%c~%s%%~w~~n~%sl~n~%s", VehicleProperty:vehicleID[SPEED], healthColor, FormatNumber(healthPercentage, 2, '.', ','), fuelColor, FormatNumber(fuelPercentage, 2, '.', ','), FormatNumber(vehicleModels[modelID - 400][VEHICLEMODEL_FUELUSAGE], 1, '.', ','), FormatNumber(VehicleProperty:vehicleID[MILEAGE], 2, '.', ','));
				PlayerTextDrawSetString(playerID, PTextDraw:playerID[SPEEDO_COLUMN2], textDrawString);
				PlayerTextDrawSetString(playerID, PTextDraw:playerID[VEHICLENAME], vehicleModels[modelID - 400][VEHICLEMODEL_NAME]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[SPEEDO_COLUMN1]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[SPEEDO_COLUMN2]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[VEHICLENAME]);
				inVehicle = true;
				if (VehicleProperty:vehicleID[SPEED] && !seatID)
				{
					CheckSpeedCamera(playerID);
				}
			}
		}
		if (!inVehicle)
		{
			PlayerTextDrawHide(playerID, PTextDraw:playerID[SPEEDO_COLUMN1]);
			PlayerTextDrawHide(playerID, PTextDraw:playerID[SPEEDO_COLUMN2]);
			PlayerTextDrawHide(playerID, PTextDraw:playerID[VEHICLENAME]);
		}
		if (PVar:playerID[SHOWPOS])
		{
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			new Float:angle;
			GetPlayerPos(playerID, posX, posY, posZ);
			GetPlayerFacingAngle(playerID, angle);
			FormatNew:textDrawString[100]("~w~X: ~g~%.2f~w~~n~Y: ~g~%.2f~w~~n~Z: ~g~%.2f~w~~n~A: ~g~%.2f~w~~n~I: ~g~%d", posX, posY, posZ, angle, GetPlayerInterior(playerID));
			PlayerTextDrawSetString(playerID, PTextDraw:playerID[SHOWPOS], textDrawString);
		}
	}
}