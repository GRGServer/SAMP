PlayRadioStation(playerID, id)
{
	if (id)
	{
		PlayAudioStreamForPlayer(playerID, GetMySQLValue("radiostations", "URL", "ID", val2str(id)));
		new vehicleID = GetPlayerVehicleID(playerID);
		VehicleProperty:vehicleID[RADIOSTATION] = id;
		if (VehicleProperty:vehicleID[SAVEID])
		{
			SetMySQLValue("vehicles", "LastRadioStation", val2str(id), "ID", val2str(VehicleProperty:vehicleID[SAVEID]));
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