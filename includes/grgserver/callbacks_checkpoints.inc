public OnPlayerEnterCheckpoint(playerid)
{
	switch (GetPVarInt(playerid, "CurrentCheckpoint"))
	{
		case CHECKPOINT_WALKTOPLANEEXIT:
		{
			// TODO: Fade to black
			// TeleportTo(playerid, posX, posY, posZ, angle, 0, 0);
		}
		case CHECKPOINT_WALKTOSEAT:
		{
			TogglePlayerControllable(playerid, false);
			// TODO: Sit down (Animation)
			SetTimerEx("Timer_FlyWithPlane", 5000, false, "ii", playerid, 1);
		}
	}
}