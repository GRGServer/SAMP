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
		case CHECKPOINT_TRAILER1:
		{
			SetPlayerCheckpointEx(playerid, CHECKPOINT_ORDEREND1, -1106.5825, -1620.9615, 75.9425, 10.0);

		}
		case CHECKPOINT_TRAILER2:
		{
			SetPlayerCheckpointEx(playerid, CHECKPOINT_ORDEREND2, 597.9862, 871.9865, -43.4022, 10.0);
		}
		case CHECKPOINT_TRAILER3:
		{
			SetPlayerCheckpointEx(playerid, CHECKPOINT_ORDEREND3, 2648.7891, 2732.5945, 10.8203, 10.0);
		}
		case CHECKPOINT_TRAILER4:
		{
			SetPlayerCheckpointEx(playerid, CHECKPOINT_ORDEREND4, -64.0349, 41.7692, 3.1103, 10.0);
		}
		case CHECKPOINT_ORDEREND1:
		{
			new Float:bank = 300.00;
			SendClientMessageEx(playerid, COLOR_INFO, 551, bank);
			SendClientMessageEx(playerid, COLOR_INFO, 552);
			GivePlayerMoneyEx(playerid, MONEY_BANK, bank);
		}
		case CHECKPOINT_ORDEREND2:
		{
			new Float:bank2 = 600.00;
			SendClientMessageEx(playerid, COLOR_INFO, 551, bank2);
			SendClientMessageEx(playerid, COLOR_INFO, 552);
			GivePlayerMoneyEx(playerid, MONEY_BANK, bank2);
		}
		case CHECKPOINT_ORDEREND3:
		{
			new Float:bank3 = 1200.00;
			SendClientMessageEx(playerid, COLOR_INFO, 551, bank3);
			SendClientMessageEx(playerid, COLOR_INFO, 552);
			GivePlayerMoneyEx(playerid, MONEY_BANK, bank3);
		}
		case CHECKPOINT_ORDEREND4:
		{
			new Float:bank4 = 900.00;
			SendClientMessageEx(playerid, COLOR_INFO, 551, bank4);
			SendClientMessageEx(playerid, COLOR_INFO, 552);
			GivePlayerMoneyEx(playerid, MONEY_BANK, bank4);
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