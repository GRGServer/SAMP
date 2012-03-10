GivePlayerMoneyEx(playerID, Float:amount)
{
	PVar:playerID[MONEY] = floatadd(PVar:playerID[MONEY], amount);
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playerID, floatround(PVar:playerID[MONEY], floatround_tozero) * 100);
}