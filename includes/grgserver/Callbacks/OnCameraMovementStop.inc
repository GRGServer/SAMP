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
		case 6:// Andromada fly-by
		{
			StartScreenFader(playerID, 0, 0, 0, 2, 6000, FADE_START_INPLANE2_BLACK);
			FormatNew:string[20](LanguageString(playerID, 274), 7);
			GameTextForPlayer(playerID, string, 6000, 1);
		}
		default:
		{
			SetCameraBehindPlayer(playerID);
			TogglePlayerControllable(playerID, true);
		}
	}
}