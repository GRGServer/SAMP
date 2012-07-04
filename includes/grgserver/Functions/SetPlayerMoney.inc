SetPlayerMoney(playerID, type, Float:amount, add = false)
{
	switch (type)
	{
		case MONEY_BANK:// Money on bank account
		{
			if (strval(GetMySQLValue("users", "bankAccountId", "id", val2str(PVar:playerID[USERID]))))
			{
				if (add)
				{
					PVar:playerID[BANKMONEY] = floatadd(PVar:playerID[BANKMONEY], amount);
				}
				else
				{
					PVar:playerID[BANKMONEY] = amount;
				}
				return true;
			}
			else
			{
				return SetPlayerMoney(playerID, MONEY_CASH, amount, add);
			}
		}
		case MONEY_CASH:// Directly usable money (Shown on the player's screen)
		{
			if (add)
			{
				PVar:playerID[MONEY] = floatadd(PVar:playerID[MONEY], amount);
			}
			else
			{
				PVar:playerID[MONEY] = amount;
			}
			if (PVar:playerID[MONEY] > MAX_MONEY)
			{
				PVar:playerID[MONEY] = MAX_MONEY;
				SendClientMessageEx(playerID, COLOR_ERROR, 492, MAX_MONEY);
				printf("%s reached MAX_MONEY (%2f)", GetPlayerNameEx(playerID), MAX_MONEY);
			}
			ResetPlayerMoney(playerID);
			GivePlayerMoney(playerID, floatround(PVar:playerID[MONEY] * 100, floatround_tozero));
			return true;
		}
	}
	return false;
}