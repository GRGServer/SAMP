public OnPlayerEnterRaceCheckpoint(playerid)
{
	new removeCheckpoint = true;
	switch (PVar:playerid[CURRENTRACECHECKPOINT])
	{
		case CHECKPOINT_NAVIGPS:
		{
			removeCheckpoint = !ShowGPSCheckpoint(playerid, PVar:playerid[GPS_ID] + 1);
		}
		default:
		{
			removeCheckpoint = false;
		}
	}
	if (removeCheckpoint)
	{
		RemovePlayerRaceCheckpoint(playerid);
	}
}