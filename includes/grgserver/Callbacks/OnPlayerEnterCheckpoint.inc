public OnPlayerEnterCheckpoint(playerid)
{
	new validCheckpoint = true;
	switch (PVar:playerid[CURRENTCHECKPOINT])
	{
		case CHECKPOINT_INPLANE_EXIT:
		{
			StartScreenFader(playerid, 0, 0, 0, 2, 0, FADE_START_PLANEEXIT_BLACK);
			TogglePlayerControllable(playerid, false);
		}
		case CHECKPOINT_TUTORIAL_SPEAKER1:
		{
			ShowMessage(playerid, 1, 3000);
		}
		default:
		{
			validCheckpoint = false;
		}
	}
	if (validCheckpoint)
	{
		RemovePlayerCheckpoint(playerid);
	}
}