CheckSpeedCamera(playerID)
{
	new closestSpeedCamera = -1;
	new Float:closestObjectDistance;
	Foreach(arrayIndex, speedCameras)
	{
		if (speedCameras[arrayIndex][SPEEDCAMERA_OBJECTID] && IsValidDynamicObject(speedCameras[arrayIndex][SPEEDCAMERA_OBJECTID]))
		{
			new Float:position[3];
			GetDynamicObjectPos(speedCameras[arrayIndex][SPEEDCAMERA_OBJECTID], position[0], position[1], position[2]);
			new Float:distance = GetPlayerDistanceFromPoint(playerID, position[0], position[1], position[2]);
			if (distance < closestObjectDistance || closestSpeedCamera == -1)
			{
				closestSpeedCamera = arrayIndex;
				closestObjectDistance = distance;
			}
		}
	}

	new vehicleID = GetPlayerVehicleID(playerID);

	if (!vehicleID || closestSpeedCamera == -1 || closestObjectDistance > SPEEDCAMERA_DISTANCE)
	{
		PVar:playerID[SPEEDCAM_LIMITREACHED] = false;
		return false;
	}

	if (vehicleID && VehicleProperty:vehicleID[SPEED] > speedCameras[closestSpeedCamera][SPEEDCAMERA_SPEEDLIMIT] + SPEEDCAMERA_TOLERANCE)
	{
		if (!PVar:playerID[SPEEDCAM_LIMITREACHED])
		{
			new speedDifference = VehicleProperty:vehicleID[SPEED] - speedCameras[closestSpeedCamera][SPEEDCAMERA_SPEEDLIMIT];
			new Float:price = float(speedDifference);
			new vehicleType[STRINGLENGTH_VEHICLETYPE];
			strcat(vehicleType, vehicleModels[GetVehicleModel(vehicleID) - 400][VEHICLEMODEL_TYPE]);
			PVar:playerID[SPEEDCAM_LIMITREACHED] = true;
			PVar:playerID[SPEEDLIMITPOINTS]++;
			SendClientMessageEx(playerID, COLOR_WARNING, StringID:453("You are driving too fast and have to pay %m! (%d km/h; Max: %d km/h)"), price, VehicleProperty:vehicleID[SPEED], speedCameras[closestSpeedCamera][SPEEDCAMERA_SPEEDLIMIT]);
			SendClientMessageEx(playerID, COLOR_WARNING, StringID:39("Your speed limit points were increased to %d points!"), PVar:playerID[SPEEDLIMITPOINTS]);
			GivePlayerMoneyEx(playerID, MONEY_CASH, -price);
			if (PVar:playerID[SPEEDLIMITPOINTS] >= MAX_SPEEDLIMITPOINTS && HasLicense(playerID, vehicleType))
			{
				MySQLQuery("DELETE FROM `licenses` WHERE `userId` = '%d' AND `type` = '%s'", PVar:playerID[USERID], MySQLEscapeString(vehicleType));
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:44("You now have reached the limit of %d speed limit points and lost your driving license!"), MAX_SPEEDLIMITPOINTS);
			}
		}
	}
	else
	{
		PVar:playerID[SPEEDCAM_LIMITREACHED] = false;
	}

	return true;
}