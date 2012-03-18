PlayRadioStation(playerID, id)
{
	if (id)
	{
		PlayAudioStreamForPlayer(playerID, GetMySQLValue("radiostations", "URL", "ID", val2str(id)));
		new vehicleID = GetPlayerVehicleID(playerID);
		vehicles[vehicleID][VEHICLE_RADIOSTATION] = id;
		if (vehicles[vehicleID][VEHICLE_SAVEID])
		{
			SetMySQLValue("savedvehicles", "LastRadioStation", val2str(id), "ID", val2str(vehicles[vehicleID][VEHICLE_SAVEID]));
		}
		TextDrawSetString(PVar:playerID[TEXTDRAW_RADIOSTATION], GetMySQLValue("radiostations", "Name", "ID", val2str(id)));
		TextDrawShowForPlayer(playerID, PVar:playerID[TEXTDRAW_RADIOSTATION]);
		KillTimer(PVar:playerID[RADIODISPLAYTIMER]);
		PVar:playerID[RADIODISPLAYTIMER] = SetTimerEx("Timer_HideRadioDisplay", TIMER_HIDERADIODISPLAY, false, "i", playerID);
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 131);
	}
}