PlayRadioStation(playerID, id)
{
	if (id)
	{
		PlayAudioStreamForPlayer(playerID, GetMySQLValue("radiostations", "URL", "ID", val2str(id)));
		new vehicleID = GetPlayerVehicleID(playerID);
		vehicles[vehicleID][VEHICLE_RADIOSTATION] = id;
		if (vehicles[vehicleID][VEHICLE_SAVEID])
		{
			SetMySQLValue("vehicles", "LastRadioStation", val2str(id), "ID", val2str(vehicles[vehicleID][VEHICLE_SAVEID]));
		}
		PlayerTextDrawSetString(playerID, PTextDraw:playerID[RADIOSTATION], GetMySQLValue("radiostations", "Name", "ID", val2str(id)));
		PlayerTextDrawShow(playerID, PTextDraw:playerID[RADIOSTATION]);
		KillTimer(PVar:playerID[RADIODISPLAYTIMER]);
		PVar:playerID[RADIODISPLAYTIMER] = SetTimerEx("Timer_HideRadioDisplay", TIMER_HIDERADIODISPLAY, false, "i", playerID);
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 131);
	}
}