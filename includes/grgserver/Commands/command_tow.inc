//TODO: Fahrzeug wird nicht an den TowTruck gehängt. Finde Fehler nicht /*Aerox*/
CMD:tow(playerid, params[], 285)
{
	if(PVar:playerid[JOBID] == JOB_ADAC)
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			new vehID = GetPlayerVehicleID(playerid);
			if(GetVehicleModel(vehID) == 525)
			{
				new Float:x, Float:y, Float:z;
				GetVehiclePos(vehID,x,y,z);
				new trailer;
				GetVehicleWithinDistance(playerid, x, y, z, 10.0, trailer);
				AttachTrailerToVehicle(trailer, vehID);
			}
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_ERROR, 286);
			return 1;
		}
	}
	else 
	{
		SendClientMessageEx(playerid, COLOR_ERROR, 287);
		return 1;
	}
	return COMMAND_OK;
}