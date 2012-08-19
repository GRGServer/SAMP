/**
 * <summary>
 *	This callback gets called once the message was shown to the player and the time specified in ShowMessage has elapsed.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player for which the message was shown.
 * </param>
 *
 * <param name="messageID">
 *	The ID of the shown message.
 * </param>
 */

forward OnMessageShown(playerID, messageID);
public OnMessageShown(playerID, messageID)
{
	switch (messageID)
	{
		case 1:
		{
			ShowMessage(playerID, 2, 3000);
		}
		case 2:
		{
			ShowMessage(playerID, 3, 3000);
		}
		case 3:
		{
			ShowMessage(playerID, 4, 3000);
		}
		case 4:
		{
			ShowMessage(playerID, 5, 3000);
		}
		case 5:
		{
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_TUTORIAL_S1_END, 0);
		}
		case 6:
		{
			//InterpolateCameraToPos(playerID, 1082.5531, 1068.0121, 10.8359, 2000, CAMERA_MOVE);
			//InterpolateCameraToLookAt(playerID, 1046.4423, 1021.8431, 33.3791, 2000, CAMERA_MOVE);
			ShowMessage(playerID, 7, 6000);
		}
		case 7:
		{
			InterpolateCameraToPos(playerID, 1043.6639, 1015.4567, 12.9713, 2000, CAMERA_MOVE);
			InterpolateCameraToLookAt(playerID, 1045.3195, 1010.8120, 11.0000, 2000, CAMERA_MOVE);
			ShowMessage(playerID, 8, 5000);
		}
		case 8:
		{
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_TUTORIAL_BANK_END, 0);
		}
		case 10:
		{
			SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_BUS3, 1730.177734, 1481.119628, 10.812820, 1.5);
			ShowMessage(playerID, 11, 3000);
		}
		case 19:
		{
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_TUTORIALEND2, 0);
		}
		case 20:
		{
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_TUTORIALEND3, 0);
		}
		case 21:
		{
			ShowMessage(playerID, 22, 3000);
		}
		case 22:
		{
			ShowMessage(playerID, 23, 3000);
		}
		case 23:
		{
			ShowMessage(playerID, 24, 3000);
		}
		case 24:
		{
			ShowMessage(playerID, 25, 3000);
		}
		case 25:
		{
			ShowDialog:DrivingSchool_StartDriving(playerID);
		}
		case 26:
		{
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_DRVSCHOOL_STARTDRIVING, 0);
		}
		case 27:
		{
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_DRVSCHOOL_EXIT, 0);
		}
	}
}