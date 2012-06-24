public OnPlayerEnterRaceCheckpoint(playerid)
{
	DisablePlayerRaceCheckpoint(playerid);
	switch (PVar:playerid[CURRENTRACECHECKPOINT])
	{
		case CHECKPOINT_NAVIGPS:
		{
			ShowGPSCheckpoint(playerid, PVar:playerid[GPS_ID] + 1);
		}
	}
}