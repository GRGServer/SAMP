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
			ShowSubtitle(playerID, LanguageString(playerID, 281));
			//SetPlayerCheckpointEx(playerID, CHECKPOINT_TUTORIAL_TAXI);
		}
	}
}