CMD:sit(playerID, params[], StringID:438("Sit down or stand up"))
{
	new Float:rotation;
	sscanf(params, "f", rotation);
	if (PVar:playerID[ISSITTING])
	{
		ClearAnimations(playerID);
		if (rotation)
		{
			RotatePlayer(playerID, rotation);
		}
		PVar:playerID[ISSITTING] = false;
	}
	else
	{
		if (rotation)
		{
			RotatePlayer(playerID, rotation);
		}
		ApplyAnimation(playerID, "PED", "SEAT_idle", 4.0, 1, 0, 0, 0, 0);
		PVar:playerID[ISSITTING] = true;
	}
	return COMMAND_OK;
}