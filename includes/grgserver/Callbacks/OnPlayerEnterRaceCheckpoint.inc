public OnPlayerEnterRaceCheckpoint(playerid)
{
	switch (PVar:playerid[CURRENTRACECHECKPOINT])
	{
		case CHECKPOINT_MISSION:
		{
			if (PVar:playerid[CPMISSION_VEHICLEID] != -1)// Require a vehicle if vehicleID is not -1
			{
				new vehicleID = GetPlayerVehicleID(playerid);
				if (!vehicleID)// Do not allow to enter the checkpoint if the player is not in any vehicle
				{
					SendClientMessageEx(playerid, COLOR_ERROR, StringID:612("You have to be in a vehicle to use this checkpoint!"));
					return false;
				}
				if (vehicleID != PVar:playerid[CPMISSION_VEHICLEID])// Do not allow to enter the checkpoint if the vehicleID does not match the current vehicle ID
				{
					SendClientMessageEx(playerid, COLOR_ERROR, StringID:613("You are not in the required vehicle!"));
					return false;
				}
			}
			DisablePlayerRaceCheckpoint(playerid);
			NextMissionCheckpoint(playerid);
		}
		case CHECKPOINT_NAVIGPS:
		{
			DisablePlayerRaceCheckpoint(playerid);
			ShowGPSCheckpoint(playerid, PVar:playerid[GPS_ID] + 1);
		}
	}
	return true;
}