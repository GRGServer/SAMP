forward OnCameraMovementStop(playerID, movementID);
public OnCameraMovementStop(playerID, movementID)
{
	switch (movementID)
	{
		case 3:// Gas station
		{
			StartScreenFader(playerID, 0, 0, 0, 5, 0, 1);
		}
		default:
		{
			SetCameraBehindPlayer(playerID);
			TogglePlayerControllable(playerID, true);
		}
	}
}