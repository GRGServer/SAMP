ShowMessage(playerID, messageID, waitTime = 0)
{
	new stringID;
	switch (messageID)
	{
		case 1:
		{
			stringID = 276;
		}
		case 2:
		{
			stringID = 277;
		}
		case 3:
		{
			stringID = 278;
		}
		case 4:
		{
			stringID = 279;
		}
		case 5:
		{
			stringID = 280;
		}
	}
	if (stringID)
	{
		ShowSubtitle(playerID, LanguageString(playerID, stringID));
		SetTimerEx("OnMessageShown", waitTime, false, "dd", playerID, messageID);
	}
}