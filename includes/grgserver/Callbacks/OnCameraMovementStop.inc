forward OnCameraMovementStop(playerID, movementID);
public OnCameraMovementStop(playerID, movementID)
{
	switch (movementID)
	{
		case 3:// Gas station
		{
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_GASSTATION_BLACK);
		}
		case 4:// Respawn (Fly from sky to spawn)
		{
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_RESPAWN_BLACK);
		}
		default:
		{
			SetCameraBehindPlayer(playerID);
			TogglePlayerControllable(playerID, true);
		}
	}
}