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
			case FADE_BUILDINGBOUGHT_BLACK:
			{
				TogglePlayerControllable(playerID, true);
				SetCameraBehindPlayer(playerID);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_BUILDINGBOUGHT_BACK);
			}
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
				ShowSubtitle(playerID, LanguageString(playerID, 291));
			}
			case FADE_START_INPLANE2_BLACK:
			{
				SetPlayerCheckpointEx(playerID, CHECKPOINT_INPLANE_EXIT, 2.6446, 33.1288, 1199.5938, 0.8);
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
				SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_SPEAKER1, 1715.0739, 1616.4, 10.0717, 1.0);
				SetPlayerPosEx(playerID, 1674.8492, 1582.8899, 13.9236, 0);
				SetPlayerFacingAngle(playerID, 0.0);
				SetCameraBehindPlayer(playerID);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_START_PLANEEXIT_BACK);
			}
			case FADE_TUTORIAL_BANK_END_BACK:
			{
				ShowSubtitle(playerID, LanguageString(playerID, 295));
				TogglePlayerControllable(playerID, true);
			}
			case FADE_TUTORIAL_BANK_END_BLACK:
			{
				SetCameraBehindPlayer(playerID);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIAL_BANK_END_BACK);
			}
			case FADE_TUTORIAL_BANK_START_BACK:
			{
				ShowMessage(playerID, 6, 3000);
			}
			case FADE_TUTORIAL_BANK_START_BLACK:
			{
				SetPlayerCameraPos(playerID, -2740.1819, 405.7733, 4.8635);
				SetPlayerCameraLookAt(playerID, -2765.4817, 384.6495, 18.3012);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIAL_BANK_START_BACK);
			}
			case FADE_TUTORIAL_S1_END_BACK:
			{
				TogglePlayerControllable(playerID, true);
				SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_BANK, -2757.0632, 375.7754, 4.3342, 1.5);
				ShowSubtitle(playerID, LanguageString(playerID, 281));
				//SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_TAXI);
			}
			case FADE_TUTORIAL_S1_END_BLACK:
			{
				SetPlayerPos(playerID, 1715.0995, 1615.1752, 10.0156);
				SetPlayerFacingAngle(playerID, 180.0);
				SetCameraBehindPlayer(playerID);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIAL_S1_END_BACK);
			}
			case FADE_TUTORIAL_S1_START_BACK:
			{
				ShowMessage(playerID, 1, 3000);
			}
			case FADE_TUTORIAL_S1_START_BLACK:
			{
				SetPlayerPos(playerID, 1714.5767, 1618.8486, 10.1172);
				SetPlayerFacingAngle(playerID, 5.3266);
				SetPlayerCameraPos(playerID, 1716.6685, 1620.3689, 11.1172);
				SetPlayerCameraLookAt(playerID, 1712.6682, 1619.2202, 10.1172);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIAL_S1_START_BACK);
			}
		}
	}
}