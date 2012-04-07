GivePlayerMoneyEx(playerID, type, Float:amount)
{
	SetPlayerMoney(playerID, type, floatadd(PVar:playerID[MONEY], amount));
}