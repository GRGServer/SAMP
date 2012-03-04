public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{
		StopRadioStation(playerid);
	}
}