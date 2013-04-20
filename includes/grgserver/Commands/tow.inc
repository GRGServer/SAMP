CMD:tow(playerID, params[], 285)
{
	if (PVar:playerID[JOBID] == JOB_ADAC)
	{
		if (IsPlayerInAnyVehicle(playerID))
		{
			new vehicleID = GetPlayerVehicleID(playerID);
			if (GetVehicleModel(vehicleID) == 525)
			{
				if (IsTrailerAttachedToVehicle(vehicleID))
				{
					DetachTrailerFromVehicle(vehicleID);
					SendClientMessageEx(playerID, COLOR_INFO, "289");
					return COMMAND_OK;
				}
				else
				{
					new Float:posX;
					new Float:posY;
					new Float:posZ;
					GetVehiclePos(vehicleID, posX, posY, posZ);
					new trailerVehicleID = GetClosestVehicleInRange(posX, posY, posZ, 10.0, vehicleID);
					if (trailerVehicleID == INVALID_VEHICLE_ID)
					{
						SendClientMessageEx(playerID, COLOR_ERROR, "288");
						return COMMAND_ERROR;
					}
					else
					{
						AttachTrailerToVehicle(trailerVehicleID, vehicleID);
						SendClientMessageEx(playerID, COLOR_INFO, "290");
						return COMMAND_OK;
					}
				}
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, "286");
				return COMMAND_ERROR;
			}
		}
		else
		{
			return COMMAND_NOT_IN_VEHICLE;
		}
	}
	else 
	{
		return COMMAND_PERMISSION_DENIED;
	}
}