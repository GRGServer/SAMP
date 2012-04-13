forward OnScreenFadeStop(playerID, extraID);
public OnScreenFadeStop(playerID, extraID)
{
	switch (extraID)
	{
		case 1:// Gas station camera movement (Fade to black)
		{
			SetCameraBehindPlayer(playerID);
			StartScreenFader(playerID, 0, 0, 0, -5, 0, 2);
		}
		case 2:// Gas station camera movement (Fade back to game)
		{
			TogglePlayerControllable(playerID, true);
		}
	}
}