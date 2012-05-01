public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{
		StopRadioStation(playerid);
	}
	if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		new isPassenger;
		if (newstate == PLAYER_STATE_PASSENGER)
		{
			isPassenger = true;
		}
		if (!OnPlayerEnteredVehicle(playerid, GetPlayerVehicleID(playerid), isPassenger))
		{
			RemovePlayerFromVehicle(playerid);
		}
	}
}