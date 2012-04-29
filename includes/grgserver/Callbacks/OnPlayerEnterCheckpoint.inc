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
		case CHECKPOINT_NAVITARGET:
		{
			SendClientMessageEx(playerid, COLOR_INFO, 344);
			PlaySound(playerid, SOUND_NAVITARGETREACHED);
		}
		case CHECKPOINT_TUTORIAL_BANK:
		{
			StartScreenFader(playerid, 0, 0, 0, 5, 0, FADE_TUTORIAL_BANK_START_BLACK);
			TogglePlayerControllable(playerid, false);
		}
		case CHECKPOINT_TUTORIAL_SPEAKER1:
		{
			StartScreenFader(playerid, 0, 0, 0, 5, 0, FADE_TUTORIAL_S1_START_BLACK);
			TogglePlayerControllable(playerid, false);
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