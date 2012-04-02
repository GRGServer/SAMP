Timer:ResetCameraMovement(playerID)
{
	SetCameraBehindPlayer(playerID);
	TogglePlayerControllable(playerID, true);
}