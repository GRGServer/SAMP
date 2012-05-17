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
			new modelID = GetVehicleModel(vehicleID);
			if (modelID >= 400 && modelID <= 611)
			{
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
					vehicles[vehicleID][VEHICLE_CURRENTFUEL] = floatsub(vehicles[vehicleID][VEHICLE_CURRENTFUEL], distance * floatdiv(vehicleModels[modelID - 400][VEHICLEMODEL_FUELUSAGE], 100));
				}
				fuelPercentage = floatmul(floatdiv(vehicles[vehicleID][VEHICLE_CURRENTFUEL], vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL]), 100);
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
				FormatNew:textDrawString[60]("~n~%d Km/h~n~~%c~%s%%~w~~n~~%c~%s%%~w~~n~%sl~n~%s", speed, healthColor, FormatNumber(healthPercentage, 2, '.', ','), fuelColor, FormatNumber(fuelPercentage, 2, '.', ','), FormatNumber(vehicleModels[modelID - 400][VEHICLEMODEL_FUELUSAGE], 1, '.', ','), FormatNumber(vehicles[vehicleID][VEHICLE_MILEAGE], 2, '.', ','));
				PlayerTextDrawSetString(playerID, PTextDraw:playerID[SPEEDO_COLUMN2], textDrawString);
				PlayerTextDrawSetString(playerID, PTextDraw:playerID[VEHICLENAME], vehicleModels[modelID - 400][VEHICLEMODEL_NAME]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[SPEEDO_COLUMN1]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[SPEEDO_COLUMN2]);
				PlayerTextDrawShow(playerID, PTextDraw:playerID[VEHICLENAME]);
				inVehicle = true;
				if (speed)
				{
					distance = 0;
					new objectID = GetClosestObjectByModel(playerID, 18880, distance);// Search closest speed camera
					if (objectID && distance <= 40)
					{
						if (objectID != PVar:playerID[SPEEDCAM_INRANGE])
						{
							PVar:playerID[SPEEDCAM_INRANGE] = objectID;
							MySQLQuery("SELECT * FROM `speedcameras` WHERE `ObjectID` = '%d'", Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID));
							mysql_store_result();
							PVar:playerID[SPEEDCAM_SPEEDLIMIT] = strval(GetMySQLField("SpeedLimit"));
							mysql_free_result();
							if (!PVar:playerID[SPEEDCAM_SPEEDLIMIT])
							{
								printf("Speed camera object without speed camera data found or speed limit is zero (Object %d)", Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID));
							}
						}
						if (!PVar:playerID[SPEEDCAM_LIMITREACHED] && PVar:playerID[SPEEDCAM_SPEEDLIMIT] && speed > PVar:playerID[SPEEDCAM_SPEEDLIMIT])
						{
							PVar:playerID[SPEEDCAM_LIMITREACHED] = true;
							FormatNew:string[100]("You are driving too fast (%d km/h; Max: %d km/h", speed, PVar:playerID[SPEEDCAM_SPEEDLIMIT]);
							SendClientMessage(playerID, COLOR_ERROR, string);
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