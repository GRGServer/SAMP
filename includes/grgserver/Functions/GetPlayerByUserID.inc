GetPlayerByUserID(userID)
{
	LoggedInPlayers(playerID)
	{
		if (PVar:playerID[USERID] == userID)
		{
			return playerID;
		}
	}
	return INVALID_PLAYER_ID;
}