SetPlayerMoney(playerID, Float:amount)
{
	SetPVar:playerID[MONEY](amount);
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playerID, floatround(amount, floatround_tozero) * 100);
}