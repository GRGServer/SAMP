GivePlayerMoneyEx(playerID, Float:amount)
{
	SetPVar:playerID[MONEY](floatadd(GetPVar:playerID[MONEY], amount));
	ResetPlayerMoney(playerID);
	GivePlayerMoney(playerID, floatround(GetPVar:playerID[MONEY], floatround_tozero) * 100);
}