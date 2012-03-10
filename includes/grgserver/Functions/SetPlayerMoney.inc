SetPlayerMoney(playerID, Float:amount)
{
	PVar:playerID[MONEY] = amount;
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playerID, floatround(amount, floatround_tozero) * 100);
}