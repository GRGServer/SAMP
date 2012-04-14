SetPlayerMoney(playerID, type, Float:amount)
{
	if (amount > MAX_MONEY)
	{
		amount = MAX_MONEY;
		printf("%s reached MAX_MONEY (%f)", GetPlayerNameEx(playerID), MAX_MONEY);
	}
	switch (type)
	{
		case MONEY_BANK:// Money on bank account
		{
			PVar:playerID[BANKMONEY] = amount;
		}
		case MONEY_CASH:// Directly usable money (Shown on the player's screen)
		{
			PVar:playerID[MONEY] = amount;
			ResetPlayerMoney(playerID);
			GivePlayerMoney(playerID, floatround(amount * 100, floatround_tozero));
		}
	}
}