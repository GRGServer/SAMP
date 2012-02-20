public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (!ispassenger && !IsPlayerNPC(playerid))
	{
		SetVehicleEngineState(vehicleid, false);
	}
	if (!ispassenger)
	{
		if (vehicles[vehicleid][VEHICLE_SAVEID])
		{
			new ownerUserID = strval(GetMySQLValue("savedvehicles", "OwnerUserID", "ID", val2str(vehicles[vehicleid][VEHICLE_SAVEID])));
			if (ownerUserID == GetPVarInt(playerid, "UserID"))
			{
				return true;
			}
			if (ownerUserID)
			{
				SendClientMessage(playerid, COLOR_ERROR, "Dieses Fahrzeug besitzt bereits ein anderer Spieler");
				RemovePlayerFromVehicle(playerid);
			}
			else
			{
				ShowDialog(playerid, DIALOG_BUYVEHICLE, FormatNumber(floatstr(GetMySQLValue("savedvehicles", "Price", "ID", val2str(vehicles[vehicleid][VEHICLE_SAVEID]))), 2, '.', ','));
				
			}
		}
	}
	if (GetPVarInt(playerid, "RadioOn") && GetPVarInt(playerid, "LastRadioStation"))
	{
		PlayRadioStation(playerid, GetPVarInt(playerid, "LastRadioStation"));
	}
	return true;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsPlayerNPC(playerid))
	{
		SetVehicleEngineState(vehicleid, false);
	}
	SaveVehicle(vehicleid, GetPlayerInterior(playerid));
	StopRadioStation(playerid);
	return true;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	vehicles[vehicleid][VEHICLE_PAINTJOB] = paintjobid;
	return true;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	vehicles[vehicleid][VEHICLE_COLOR1] = color1;
	vehicles[vehicleid][VEHICLE_COLOR2] = color2;
	return true;
}