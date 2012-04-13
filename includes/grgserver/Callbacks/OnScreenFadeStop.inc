forward OnScreenFadeStop(playerID, extraID);
public OnScreenFadeStop(playerID, extraID)
{
	switch (extraID)
	{
		case FADE_GASSTATION_BACK:
		{
			TogglePlayerControllable(playerID, true);
		}
		case FADE_GASSTATION_BLACK:
		{
			SetCameraBehindPlayer(playerID);
			StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_GASSTATION_BACK);
		}
		case FADE_RESPAWN_BACK:
		{
			TogglePlayerControllable(playerID, true);
		}
		case FADE_RESPAWN_BLACK:
		{
			SetCameraBehindPlayer(playerID);
			StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_RESPAWN_BACK);
		}
	}
}