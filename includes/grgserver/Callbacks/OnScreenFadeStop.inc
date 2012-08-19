forward OnScreenFadeStop(playerID, extraID, subID, isTimer);
public OnScreenFadeStop(playerID, extraID, subID, isTimer)
{
	printf("OnScreenFadeStop(%d, %d, %d, %d)", playerID, extraID, subID, isTimer);
	if (isTimer)
	{
		switch (extraID)
		{
			case FADE_START_INPLANE2:
			{
				if (!subID)
				{
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_START_INPLANE2, 1);
				}
			}
		}
	}
	else
	{
		switch (extraID)
		{
			case FADE_DEATH:
			{
				if (subID)
				{
					TogglePlayerControllable(playerID, true);
					SetCameraBehindPlayer(playerID);
				}
				else
				{
					StartScreenFader(playerID, 100, 0, 0, -5, 0, FADE_DEATH, 1);
				}
			}
			case FADE_DRVSCHOOL_ENTER:
			{
				if (subID)
				{
					ShowMessage(playerID, 21, 3000);
				}
				else
				{
					SetPlayerPosEx(playerID, -2033.434570, -118.057067, 1035.171875, 3);
					SetPlayerFacingAngle(playerID, 91.393058);
					SetPlayerCameraPos(playerID, -2033.146972, -115.889007, 1035.516235);
					SetPlayerCameraLookAt(playerID, -2034.402221, -119.476028, 1035.278808);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_DRVSCHOOL_ENTER, 1);
				}
			}
			case FADE_DRVSCHOOL_EXIT:
			{
				if (subID)
				{
					TogglePlayerControllable(playerID, true);
				}
				else
				{
					SetPlayerPosEx(playerID, -2026.202636, -100.276840, 35.164062, 0);
					SetPlayerFacingAngle(playerID, 360.0);
					SetCameraBehindPlayer(playerID);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_DRVSCHOOL_EXIT, 1);
				}
			}
			case FADE_DRVSCHOOL_STARTDRIVING:
			{
				if (subID)
				{
					switch (PVar:playerID[DRIVINGSCHOOL_TYPE])
					{
						case DRIVINGSCHOOL_BIKE:
						{
							SetPlayerCheckpointEx(playerID, CHECKPOINT_DRVSCHOOL_VEHICLE, -2079.003417, -89.092414, 35.164062, 1.5);
						}
						case DRIVINGSCHOOL_CAR:
						{
							SetPlayerCheckpointEx(playerID, CHECKPOINT_DRVSCHOOL_VEHICLE, -2067.854492, -88.841735, 35.164062, 1.5);
						}
						case DRIVINGSCHOOL_TRUCK:
						{
							SetPlayerCheckpointEx(playerID, CHECKPOINT_DRVSCHOOL_VEHICLE, -2087.373535, -88.753417, 35.164062, 1.5);
						}
					}
					ShowMessage(playerID, 28, 3000);
					TogglePlayerControllable(playerID, true);
				}
				else
				{
					SetPlayerPosEx(playerID, -2026.202636, -100.276840, 35.164062, 0);
					SetPlayerFacingAngle(playerID, 30.0);
					SetCameraBehindPlayer(playerID);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_DRVSCHOOL_STARTDRIVING, 1);
				}
			}
			case FADE_GASSTATION:
			{
				if (subID)
				{
					TogglePlayerControllable(playerID, true);
					SetCameraBehindPlayer(playerID);
				}
				else
				{
					SetCameraBehindPlayer(playerID);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_GASSTATION, 1);
				}
			}
			case FADE_LEAVEPROPERTY:
			{
				if (subID)
				{
					TogglePlayerControllable(playerID, true);
					SetCameraBehindPlayer(playerID);
				}
				else
				{
					LeaveProperty(playerID);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_LEAVEPROPERTY, 1);
				}
			}
			case FADE_PROPERTYBOUGHT:
			{
				if (subID)
				{
					TogglePlayerControllable(playerID, true);
				}
				else
				{
					SetCameraBehindPlayer(playerID);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_PROPERTYBOUGHT, 1);
				}
			}
			case FADE_RESPAWN:
			{
				if (subID)
				{
					TogglePlayerControllable(playerID, true);
				}
				else
				{
					SetCameraBehindPlayer(playerID);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_RESPAWN, 1);
				}
			}
			case FADE_START_INPLANE1:
			{
				if (!subID)
				{
					TeleportToInterior(playerID, 138);
					InterpolateCameraPos(playerID, 315.8, 825.206, 1981.83, 315.075, 1035.86, 1939.33, 5000, CAMERA_CUT);
					InterpolateCameraLookAt(playerID, 313.852, 976.442, 1959.13, 316.852, 1082.44, 1925.13, 5000, CAMERA_CUT);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_START_INPLANE1, 1);
					SetTimerEx("Timer_ScreenFader", 5000, false, "dddddddd", playerID, 0, 0, 0, 5, 0, FADE_START_INPLANE2, 0);
				}
			}
			case FADE_START_INPLANE2:
			{
				if (subID)
				{
					TogglePlayerControllable(playerID, true);
					SetCameraBehindPlayer(playerID);
					ShowSubtitle(playerID, LanguageString(playerID, 291));
				}
				else
				{
					SetPlayerCheckpointEx(playerID, CHECKPOINT_INPLANE_EXIT, 2.6446, 33.1288, 1199.5938, 0.8);
					SetPlayerPosEx(playerID, 1.6918, 26.2581, 1199.5938, 1);
					SetPlayerFacingAngle(playerID, 0.0);
					SetCameraBehindPlayer(playerID);
					FormatNew:string[256](LanguageString(playerID, 274), 7);
					GameTextForPlayer(playerID, string, 8000, 1);
					SetTimerEx("Timer_ScreenFader", 8000, false, "dddddddd", playerID, 0, 0, 0, -5, 0, FADE_START_INPLANE2, 1);
				}
			}
			case FADE_START_PLANEEXIT:
			{
				if (subID)
				{
					TogglePlayerControllable(playerID, true);
					SetCameraBehindPlayer(playerID);
					ShowSubtitle(playerID, LanguageString(playerID, 275));
				}
				else
				{
					SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_SPEAKER1, 1715.0739, 1616.4, 10.0717, 1.0);
					SetPlayerPosEx(playerID, 1671.562744, 1582.741577, 14.715581, 0);
					SetPlayerFacingAngle(playerID, 0.0);
					SetCameraBehindPlayer(playerID);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_START_PLANEEXIT, 1);
				}
			}
			case FADE_TELEPORT:
			{
				if (subID)
				{
					TogglePlayerControllable(playerID, true);
					SetCameraBehindPlayer(playerID);
				}
				else
				{
					TeleportTo(playerID, PVar:playerID[TELEPORT_POSX], PVar:playerID[TELEPORT_POSY], PVar:playerID[TELEPORT_POSZ], PVar:playerID[TELEPORT_ANGLE], PVar:playerID[TELEPORT_INTERIOR], PVar:playerID[TELEPORT_VIRTUALWORLD]);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TELEPORT, 1);
				}
			}
			case FADE_TUTORIAL_BANK_END:
			{
				if (subID)
				{
					ShowSubtitle(playerID, LanguageString(playerID, 295));
					TogglePlayerControllable(playerID, true);
				}
				else
				{
					SetCameraBehindPlayer(playerID);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIAL_BANK_END, 1);
				}
			}
			case FADE_TUTORIAL_BANK_LEAVE:
			{
				if (subID)
				{
					ShowMessage(playerID, 9, 3000);
					TogglePlayerControllable(playerID, true);
				}
				else
				{
					LeaveProperty(playerID);
					SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_BUS2, 1084.606201, 1198.649169, 10.820312, 1.5);
					SetCameraBehindPlayer(playerID);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIAL_BANK_LEAVE, 1);
				}
			}
			case FADE_TUTORIAL_BANK_START:
			{
				if (subID)
				{
					ShowMessage(playerID, 6, 3000);
				}
				else
				{
					SetPlayerCameraPos(playerID, 1121.8539, 1103.0247, 47.5297);
					SetPlayerCameraLookAtEx(playerID, 1052.8539, 1024.0247, 28.5412);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIAL_BANK_START, 1);
				}
			}
			case FADE_TUTORIAL_S1_END:
			{
				if (subID)
				{
					TogglePlayerControllable(playerID, true);
					ShowMessage(playerID, 14, 3000);
				}
				else
				{
					SetPlayerPos(playerID, 1715.0995, 1615.1752, 10.0156);
					SetPlayerFacingAngle(playerID, 180.0);
					SetCameraBehindPlayer(playerID);
					SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_BUS1, 1724.885986, 1529.497802, 10.820312, 1.5);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIAL_S1_END, 1);
				}
			}
			case FADE_TUTORIAL_S1_START:
			{
				if (subID)
				{
					ShowMessage(playerID, 1, 3000);
				}
				else
				{
					SetPlayerPos(playerID, 1714.5767, 1618.8486, 10.1172);
					SetPlayerFacingAngle(playerID, 5.3266);
					SetPlayerCameraPos(playerID, 1716.6685, 1620.3689, 11.1172);
					SetPlayerCameraLookAt(playerID, 1712.6682, 1619.2202, 10.1172);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIAL_S1_START, 1);
				}
			}
			case FADE_TUTORIALEND1:
			{
				if (subID)
				{
					ShowMessage(playerID, 19, 5000);
				}
				else
				{
					SetPlayerCameraPos(playerID, -2011.800415, -75.216079, 43.945693);
					SetPlayerCameraLookAt(playerID, -2063.461914, -118.374504, 35.326580);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIALEND1, 1);
				}
			}
			case FADE_TUTORIALEND2:
			{
				if (subID)
				{
					ShowMessage(playerID, 20, 5000);
				}
				else
				{
					SetPlayerCameraPos(playerID, -2149.253906, -221.977584, 38.965263);
					SetPlayerCameraLookAt(playerID, -2179.841552, -205.179870, 36.522132);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIALEND2, 1);
				}
			}
			case FADE_TUTORIALEND3:
			{
				if (subID)
				{
					TogglePlayerControllable(playerID, true);
				}
				else
				{
					SetCameraBehindPlayer(playerID);
					StartScreenFader(playerID, 0, 0, 0, -5, 0, FADE_TUTORIALEND3, 1);
					PVar:playerID[INTUTORIAL] = false;
				}
			}
		}
	}
}