Timer:FlyWithPlane(playerID, part)
{
	switch (part)
	{
		case 1:
		{
			// TODO: Fade to black
			GameTextForPlayer(playerID, "7 Stunden später...", 3000, 1);
			SetTimerEx("Timer_FlyWithPlane", 3000, false, "ii", playerID, 2);
		}
		case 2:
		{
			// TODO: Fade back to game
			TogglePlayerControllable(playerID, true);
			SetPlayerCheckpointEx(playerID, CHECKPOINT_WALKTOPLANEEXIT);
		}
	}
}