GetOnlineTime(playerID)
{
	return PVar:playerID[ONLINETIME] + (gettime() - PVar:playerID[ONLINESINCE]);
}