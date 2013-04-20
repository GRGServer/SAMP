PlayRadioStation(playerID, radioStationID)
{
	if (radioStationID > 0 && radioStationID < sizeof(radioStations))
	{
		new vehicleID = GetPlayerVehicleID(playerID);
		if (vehicleID)
		{
			PlayAudioStreamForPlayer(playerID, radioStations[radioStationID][RADIOSTATION_URL]);
			PlayerTextDrawSetString(playerID, PTextDraw:playerID[RADIOSTATION], radioStations[radioStationID][RADIOSTATION_NAME]);
			PlayerTextDrawShow(playerID, PTextDraw:playerID[RADIOSTATION]);
			KillTimer(PVar:playerID[RADIODISPLAYTIMER]);
			PVar:playerID[RADIODISPLAYTIMER] = SetTimerEx("Timer_HideRadioDisplay", TIMER_HIDERADIODISPLAY, false, "d", playerID);
		}
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, "131");
	}
}