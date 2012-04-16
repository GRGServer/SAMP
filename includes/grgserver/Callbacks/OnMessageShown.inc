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
	}
}