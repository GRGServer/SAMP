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
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_TUTORIAL_S1_END_BLACK);
		}
		case 6:
		{
			ShowMessage(playerID, 7, 6000);
		}
		case 7:
		{
			InterpolateCameraPos(playerID, -2740.1819, 405.7733, 4.8635, -2762.4102, 378.8224, 7.4445, 2000, CAMERA_MOVE);
			InterpolateCameraLookAt(playerID, -2765.4817, 384.6495, 18.3012, -2765.2268, 375.2920, 6.3359, 2000, CAMERA_MOVE);
			ShowMessage(playerID, 8, 5000);
		}
		case 8:
		{
			StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_TUTORIAL_BANK_END_BLACK);
		}
	}
}