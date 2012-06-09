PlayRadioStation(playerID, id)
{
	if (id)
	{
		PlayAudioStreamForPlayer(playerID, GetMySQLValue("radiostations", "url", "id", val2str(id)));
		new vehicleID = GetPlayerVehicleID(playerID);
		VehicleProperty:vehicleID[RADIOSTATION] = id;
		if (VehicleProperty:vehicleID[SAVEID])
		{
			MySQLQuery("UPDATE `vehicles` SET `lastRadioStation` = '%d' WHERE `id` = '%d'", id, VehicleProperty:vehicleID[SAVEID]);
		}
		PlayerTextDrawSetString(playerID, PTextDraw:playerID[RADIOSTATION], GetMySQLValue("radiostations", "name", "id", val2str(id)));
		PlayerTextDrawShow(playerID, PTextDraw:playerID[RADIOSTATION]);
		KillTimer(PVar:playerID[RADIODISPLAYTIMER]);
		PVar:playerID[RADIODISPLAYTIMER] = SetTimerEx("Timer_HideRadioDisplay", TIMER_HIDERADIODISPLAY, false, "i", playerID);
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 131);
	}
}