public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate != PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_PASSENGER && (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER))
	{
		new isPassenger;
		if (oldstate == PLAYER_STATE_PASSENGER)
		{
			isPassenger = true;
		}
		OnPlayerLeftVehicle(playerid, PVar:playerid[OLDVEHICLEID], isPassenger);
	}
	if (oldstate != PLAYER_STATE_DRIVER && oldstate != PLAYER_STATE_PASSENGER && (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER))
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