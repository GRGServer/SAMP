/**
 * <summary>
 *	<title>This timer executes the following tasks every 250ms:</title>
 *	<item>Check payday</item>
 *	<item>Call OnPlayerZoneChange if the zone changed</item>
 *	<item>Update vehicle information in the top right corner</item>
 *	<item>Check speed cameras</item>
 *	<item>Update position in ShowPos TextDraw</item>
 * </summary>
 *
 * <remarks>
 *	Only really fast stuff should be called in this timer!
 * </remarks>
 */

Timer:Fast()
{
	LoggedInPlayers(playerID)
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
				new Float:velocityX;
				new Float:velocityY;
				new Float:velocityZ;
				new Float:health;
				new healthColor;
				new fuelColor;
				GetVehicleVelocity(vehicleID, velocityX, velocityY, velocityZ);
				GetVehicleHealth(vehicleID, health);
				new seatID = GetPlayerVehicleSeat(playerID);
				new speed = floatround(floatsqroot(floatpower(velocityX, 2) + floatpower(velocityY, 2) + floatpower(velocityZ, 2)) * 100 * 1.61);
				new Float:distance = floatdiv(speed, floatdiv(1000 * 60 * 60, TIMER_FAST));
				VehicleProperty:vehicleID[MILEAGE] = floatadd(VehicleProperty:vehicleID[MILEAGE], distance);
				new Float:healthPercentage = floatdiv(health, 10);
				if (health < 1000 && seatID == 0 && IsPlayerNPC(playerID))
				{
					SetVehicleHealth(vehicleID, 1000);
				}
				if (VehicleProperty:vehicleID[CURRENTFUEL] <= 0)
				{
					SetVehicleEngineState(vehicleID, false);
					GameTextForPlayer(playerID, LanguageString(playerID, 159), 3000, 5);
				}
				else
				{
					VehicleProperty:vehicleID[CURRENTFUEL] = floatsub(VehicleProperty:vehicleID[CURRENTFUEL], distance * floatdiv(vehicleModels[modelID - 400][VEHICLEMODEL_FUELUSAGE], 100));
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
				FormatNew:textDrawString[60]("~n~%d Km/h~n~~%c~%s%%~w~~n~~%c~%s%%~w~~n~%sl~n~%s", speed, healthColor, FormatNumber(healthPercentage, 2, '.', ','), fuelColor, FormatNumber(fuelPercentage, 2, '.', ','), FormatNumber(vehicleModels[modelID - 400][VEHICLEMODEL_FUELUSAGE], 1, '.', ','), FormatNumber(VehicleProperty:vehicleID[MILEAGE], 2, '.', ','));
				PlayerTextDrawSetString(playerID, PTextDraw:playerID[SPEEDO_COLUMN2], textDrawString);
				PlayerTextDrawSetString(playerID, PTextDraw:playerID[VEHICLENAME], vehicleModels[modelID - 400][VEHICLEMODEL_NAME]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[SPEEDO_COLUMN1]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[SPEEDO_COLUMN2]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[VEHICLENAME]);
				inVehicle = true;
				if (speed && seatID == 0)
				{
					distance = 0;
					new objectID = GetClosestObjectByModel(playerID, 18880, distance);// Search closest speed camera
					if (objectID && distance <= 40)
					{
						if (objectID != PVar:playerID[SPEEDCAM_INRANGE])
						{
							PVar:playerID[SPEEDCAM_INRANGE] = objectID;
							MySQLQuery("SELECT * FROM `speedcameras` WHERE `objectId` = '%d'", Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID));
							mysql_store_result();
							PVar:playerID[SPEEDCAM_SPEEDLIMIT] = strval(GetMySQLField("speedLimit"));
							mysql_free_result();
							if (!PVar:playerID[SPEEDCAM_SPEEDLIMIT])
							{
								printf("Speed camera object without speed camera data found or speed limit is zero (Object %d)", Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID));
							}
						}
						if (!PVar:playerID[SPEEDCAM_LIMITREACHED] && PVar:playerID[SPEEDCAM_SPEEDLIMIT] && speed > PVar:playerID[SPEEDCAM_SPEEDLIMIT])
						{
							PVar:playerID[SPEEDCAM_LIMITREACHED] = true;
							SendClientMessageEx(playerID, COLOR_ERROR, 453, speed, PVar:playerID[SPEEDCAM_SPEEDLIMIT]);
						}
					}
					else
					{
						PVar:playerID[SPEEDCAM_LIMITREACHED] = false;
					}
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