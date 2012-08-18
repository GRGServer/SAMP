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
			case FADE_DEATH_BACK:
			{
				TogglePlayerControllable(playerID, true);
				SetCameraBehindPlayer(playerID);
			}
			case FADE_DEATH_RED:
			{
				StartScreenFader(playerID, 100, 0, 0, -5, 0, FADE_DEATH_BACK);
			}
			case FADE_DRVSCHOOL_ENTER_BACK:
			{
				TogglePlayerControllable(playerID, true);// TODO: Remove after debugging
				SendClientMessage(playerID, COLOR_INFO, "Use /resetcam to reset your camera");// Just for debugging
				// TODO: Continue driving school stuff (Text, etc...)
			}
			case FADE_DRVSCHOOL_ENTER_BLACK:
			{
				SetPlayerPosEx(playerID, -2033.434570, -118.057067, 1035.171875, 3);
				SetPlayerFacingAngle(playerID, 91.393058);
				SetPlayerCameraPos(playerID, -2033.146972, -115.889007, 1035.516235);
				SetPlayerCameraLookAt(playerID, -2034.402221, -119.476028, 1035.278808);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_DRVSCHOOL_ENTER_BACK);
			}
			case FADE_GASSTATION_BACK:
			{
				TogglePlayerControllable(playerID, true);
				SetCameraBehindPlayer(playerID);
			}
			case FADE_GASSTATION_BLACK:
			{
				SetCameraBehindPlayer(playerID);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_GASSTATION_BACK);
			}
			case FADE_LEAVEPROPERTY_BACK:
			{
				TogglePlayerControllable(playerID, true);
				SetCameraBehindPlayer(playerID);
			}
			case FADE_LEAVEPROPERTY_BLACK:
			{
				LeaveProperty(playerID);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_LEAVEPROPERTY_BACK);
			}
			case FADE_PROPERTYBOUGHT_BLACK:
			{
				TogglePlayerControllable(playerID, true);
				SetCameraBehindPlayer(playerID);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_PROPERTYBOUGHT_BACK);
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
				InterpolateCameraPos(playerID, 315.8, 825.206, 1981.83, 315.075, 1035.86, 1939.33, 5000, CAMERA_CUT);
				InterpolateCameraLookAt(playerID, 313.852, 976.442, 1959.13, 316.852, 1082.44, 1925.13, 5000, CAMERA_CUT);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_START_INPLANE1_BACK);
				SetTimerEx("Timer_ScreenFader", 5000, false, "ddddddd", playerID, 0, 0, 0, 5, 0, FADE_START_INPLANE2_BLACK);
			}
			case FADE_START_INPLANE2_BACK:
			{
				TogglePlayerControllable(playerID, true);
				SetCameraBehindPlayer(playerID);
				ShowSubtitle(playerID, LanguageString(playerID, 291));
			}
			case FADE_START_INPLANE2_BLACK:
			{
				SetPlayerCheckpointEx(playerID, CHECKPOINT_INPLANE_EXIT, 2.6446, 33.1288, 1199.5938, 0.8);
				SetPlayerPosEx(playerID, 1.6918, 26.2581, 1199.5938, 1);
				SetPlayerFacingAngle(playerID, 0.0);
				SetCameraBehindPlayer(playerID);
				FormatNew:string[256](LanguageString(playerID, 274), 7);
				GameTextForPlayer(playerID, string, 8000, 1);
				SetTimerEx("Timer_ScreenFader", 8000, false, "ddddddd", playerID, 0, 0, 0, -5, 0, FADE_START_INPLANE2_BACK);
			}
			case FADE_START_PLANEEXIT_BACK:
			{
				TogglePlayerControllable(playerID, true);
				SetCameraBehindPlayer(playerID);
				ShowSubtitle(playerID, LanguageString(playerID, 275));
			}
			case FADE_START_PLANEEXIT_BLACK:
			{
				SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_SPEAKER1, 1715.0739, 1616.4, 10.0717, 1.0);
				SetPlayerPosEx(playerID, 1671.562744, 1582.741577, 14.715581, 0);
				SetPlayerFacingAngle(playerID, 0.0);
				SetCameraBehindPlayer(playerID);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_START_PLANEEXIT_BACK);
			}
			case FADE_TELEPORT_BACK:
			{
				TogglePlayerControllable(playerID, true);
				SetCameraBehindPlayer(playerID);
			}
			case FADE_TELEPORT_BLACK:
			{
				TeleportTo(playerID, PVar:playerID[TELEPORT_POSX], PVar:playerID[TELEPORT_POSY], PVar:playerID[TELEPORT_POSZ], PVar:playerID[TELEPORT_ANGLE], PVar:playerID[TELEPORT_INTERIOR], PVar:playerID[TELEPORT_VIRTUALWORLD]);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TELEPORT_BACK);
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
			case FADE_TUTORIAL_BANK_LEAVE_BACK:
			{
				ShowMessage(playerID, 9, 3000);
				TogglePlayerControllable(playerID, true);
			}
			case FADE_TUTORIAL_BANK_LEAVE_BLACK:
			{
				LeaveProperty(playerID);
				SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_BUS2, 1084.606201, 1198.649169, 10.820312, 1.5);
				SetCameraBehindPlayer(playerID);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIAL_BANK_LEAVE_BACK);
			}
			case FADE_TUTORIAL_BANK_START_BACK:
			{
				ShowMessage(playerID, 6, 3000);
			}
			case FADE_TUTORIAL_BANK_START_BLACK:
			{
				SetPlayerCameraPos(playerID, 1121.8539, 1103.0247, 47.5297);
				SetPlayerCameraLookAtEx(playerID, 1052.8539, 1024.0247, 28.5412);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIAL_BANK_START_BACK);
			}
			case FADE_TUTORIAL_S1_END_BACK:
			{
				TogglePlayerControllable(playerID, true);
				ShowMessage(playerID, 14, 3000);
			}
			case FADE_TUTORIAL_S1_END_BLACK:
			{
				SetPlayerPos(playerID, 1715.0995, 1615.1752, 10.0156);
				SetPlayerFacingAngle(playerID, 180.0);
				SetCameraBehindPlayer(playerID);
				SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_BUS1, 1724.885986, 1529.497802, 10.820312, 1.5);
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
			case FADE_TUTORIALEND1_BACK:
			{
				ShowMessage(playerID, 19, 5000);
			}
			case FADE_TUTORIALEND1_BLACK:
			{
				SetPlayerCameraPos(playerID, -2011.800415, -75.216079, 43.945693);
				SetPlayerCameraLookAt(playerID, -2063.461914, -118.374504, 35.326580);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIALEND1_BACK);
			}
			case FADE_TUTORIALEND2_BACK:
			{
				ShowMessage(playerID, 20, 5000);
			}
			case FADE_TUTORIALEND2_BLACK:
			{
				SetPlayerCameraPos(playerID, -2149.253906, -221.977584, 38.965263);
				SetPlayerCameraLookAt(playerID, -2179.841552, -205.179870, 36.522132);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIALEND2_BACK);
			}
			case FADE_TUTORIALEND3_BACK:
			{
				TogglePlayerControllable(playerID, true);
			}
			case FADE_TUTORIALEND3_BLACK:
			{
				SetCameraBehindPlayer(playerID);
				StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIALEND3_BACK);
				PVar:playerID[INTUTORIAL] = false;
			}
		}
	}
}