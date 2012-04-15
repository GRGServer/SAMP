forward OnScreenFadeStop(playerID, extraID, isTimer);
public OnScreenFadeStop(playerID, extraID, isTimer)
{
	if (isTimer)
	{
		switch (extraID)
		{
			case FADE_START_INPLANE2_BLACK:
			{
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_START_INPLANE2_BACK);
			}
		}
	}
	else
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
			case FADE_START_INPLANE1_BLACK:
			{
				TeleportToInterior(playerID, 138);
				PlayCameraMovement(playerID, 6);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_START_INPLANE1_BACK);
				
			}
			case FADE_START_INPLANE2_BACK:
			{
				TogglePlayerControllable(playerID, true);
			}
			case FADE_START_INPLANE2_BLACK:
			{
				SetPlayerCheckpointEx(playerID, CHECKPOINT_INPLANE_EXIT);
				SetPlayerPosEx(playerID, 1.6918, 26.2581, 1199.5938, 1);
				SetPlayerFacingAngle(playerID, 0.0);
				SetCameraBehindPlayer(playerID);
			}
			case FADE_START_PLANEEXIT_BACK:
			{
				TogglePlayerControllable(playerID, true);
				ShowSubtitle(playerID, LanguageString(playerID, 275));
			}
			case FADE_START_PLANEEXIT_BLACK:
			{
				SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_SPEAKER1);
				SetPlayerPosEx(playerID, 1674.8492, 1582.8899, 13.9236, 0);
				SetPlayerFacingAngle(playerID, 0.0);
				SetCameraBehindPlayer(playerID);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_START_PLANEEXIT_BACK);
			}
		}
	}
}